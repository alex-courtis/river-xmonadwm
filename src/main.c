#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <wayland-client-core.h>

#include "config.h"
#include "displ.h"
#include "log.h"

#define NPFDS 2
static struct pollfd pfds[NPFDS];
static struct pollfd *pfd_wayland = NULL;
static struct pollfd *pfd_signal = NULL;

void init_pfds(void) {

	// wayland FD
	if (!pfd_wayland) {
		pfds[0].fd = wl_display_get_fd(displ->wl_display);
		pfds[0].events = POLLIN;
		pfds[0].revents = 0;
		pfd_wayland = &pfds[0];
	}

	// interesting signals
	if (!pfd_signal) {
		sigset_t mask;
		sigemptyset(&mask);
		sigaddset(&mask, SIGINT);
		sigaddset(&mask, SIGQUIT);
		sigaddset(&mask, SIGTERM);
		sigprocmask(SIG_BLOCK, &mask, NULL);

		pfds[1].fd = signalfd(-1, &mask, 0);
		pfds[1].events = POLLIN;
		pfds[1].revents = 0;
		pfd_signal = &pfds[1];
	}
}

// see Wayland Protocol docs Appendix B wl_display_prepare_read_queue
int loop(void) {

	while (!displ->terminate) {
		log_debug("");
		log_debug("loop START");
		init_pfds();

		// dispatch and prepare for next wayland event
		while (wl_display_prepare_read(displ->wl_display) != 0) {
			if (wl_display_dispatch_pending(displ->wl_display) == -1) {
				log_error_errno("wl_display_dispatch_pending failed, exiting");
				return errno;
			}
		}

		// send dispatched
		log_debug("loop prepared/dispatched");
		if (wl_display_flush(displ->wl_display) == -1) {
			log_error_errno("wl_display_flush failed, exiting");
			return errno;
		}
		log_debug("loop flushed");

		if (displ->terminate) {
			return displ->rc;
		}

		// poll for all events
		if (poll(pfds, NPFDS, -1) < 0) {
			log_error_errno("poll failed, exiting");
			return EXIT_FAILURE;
		}
		log_debug("loop polled");

		if (pfd_signal->revents & pfd_signal->events) {

			log_debug("loop read signal");

			// signal received
			struct signalfd_siginfo fdsi;
			if (read(pfd_signal->fd, &fdsi, sizeof(fdsi)) == sizeof(fdsi)) {
				return fdsi.ssi_signo;
			}
		} else if (pfd_wayland->revents & pfd_wayland->events) {

			log_debug("loop read wayland");

			// wayland events
			if (wl_display_read_events(displ->wl_display) == -1) {
				if (errno == EPIPE) {
					log_info("Wayland display terminated, exiting.");
					return EXIT_SUCCESS;
				} else {
					log_error_errno("wl_display_read_events failed, exiting");
					return errno;
				}
			}
		} else {

			// TODO is this a reasonable case?
			log_error("Unknown event received, exiting");
			return EXIT_FAILURE;
		}

		// TODO is this reachable?
		if (!displ->river_layout_manager) {
			log_info("\nRiver layout manager has departed, exiting");
			return EXIT_SUCCESS;
		}

		log_debug("loop END");
	}

	return displ->rc;
}

int main(int argc, char **argv) {
	config_parse(argc, argv);

	config_print();

	if (!getenv("WAYLAND_DISPLAY")) {
		log_error("Environment variable WAYLAND_DISPLAY not set, exiting");
		exit(EXIT_FAILURE);
	}

	if (!displ_init()) {
		exit(EXIT_FAILURE);
	}

	log_info("river-xmonadwm started");

	int rc = loop();

	displ_destroy();

	config_destroy();

	log_info("river-xmonadwm done");

	return rc;
}
