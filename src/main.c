#include <stdio.h>
#include <stdlib.h>

#include "displ.h"
#include "log.h"

#include "river-layout-v3-client-protocol.h"
#include "inc1.h"
#include "inc2.h"

void loop(void) {
	// TODO more orthodox loop with an interrupt handler
	while (wl_display_dispatch(displ->wl_display) != -1 && !displ->terminate);
}

int main(int argc, char **argv) {
	log_info("river-xmonadwm starting");

	if (!getenv("WAYLAND_DISPLAY")) {
		log_error("Environment variable WAYLAND_DISPLAY not set.");
		exit(EXIT_FAILURE);
	}

	displ_init();

	log_info("river-xmonadwm started");

	loop();

	displ_destroy();

	log_info("river-xmonadwm done");

	return 0;
}
