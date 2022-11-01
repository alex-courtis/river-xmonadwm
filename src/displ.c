#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "listeners.h"
#include "log.h"
#include "output.h"

#include "displ.h"

struct Displ *displ = NULL;

void displ_init(void) {
	struct wl_display *wl_display = wl_display_connect(NULL);
	if (!wl_display) {
		log_error("Unable to connect to the compositor. Check or set the WAYLAND_DISPLAY environment variable.");
		exit(EXIT_FAILURE);
	}

	displ = calloc(1, sizeof(struct Displ));
	displ->wl_display = wl_display;

	displ->wl_registry = wl_display_get_registry(displ->wl_display);

	wl_registry_add_listener(displ->wl_registry, registry_listener(), displ);

	if (wl_display_roundtrip(displ->wl_display) == -1) {
		log_error("First wl_display_roundtrip failed -1");
		exit(EXIT_FAILURE);
	}

	if (!displ->layout_manager) {
		log_error("Compositor does not support river_layout_v3 protocol");
		exit(EXIT_FAILURE);
	}
}

void displ_destroy(void) {
	if (!displ)
		return;

	for (struct SList *i = displ->outputs; i; i = i->nex) {
		output_destroy(i->val);
	}
	slist_free(&displ->outputs);

	if (displ->layout_manager) {
		river_layout_manager_v3_destroy(displ->layout_manager);
	}
	if (displ->wl_registry) {
		wl_registry_destroy(displ->wl_registry);
	}
	if (displ->wl_display) {
		wl_display_disconnect(displ->wl_display);
	}

	free(displ);

	displ = NULL;
}

