#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "list.h"
#include "output.h"

#include "displ.h"

struct Displ *displ = NULL;

static void global(void *data,
		struct wl_registry *wl_registry,
		uint32_t name,
		const char *interface,
		uint32_t version) {

	struct Displ *displ = data;
	displ->name = name;

	displ->interface = strdup(interface);

	if (strcmp(interface, river_layout_manager_v3_interface.name) == 0) {
		displ->layout_manager = wl_registry_bind(wl_registry, name, &river_layout_manager_v3_interface, version);
	} else if (strcmp(interface, wl_output_interface.name) == 0) {
		if (!displ->layout_manager) {
			log_error("Cannot create layout for output, missing river layout mananger.");
			exit(EXIT_FAILURE);
		}

		struct Output *output = calloc(1, sizeof(struct Output));
		slist_append(&displ->outputs, output);
		// TODO fetch and connect output
		// river_layout_manager_v3_get_layout(displ->layout_manager, data, "river-xmonadwm");
	}
}

static void global_remove(void *data,
		struct wl_registry *wl_registry,
		uint32_t name) {
	// TODO cleanup
}

static const struct wl_registry_listener listener = {
	.global = global,
	.global_remove = global_remove,
};

bool displ_connect(void) {
	displ = calloc(1, sizeof(struct Displ));

	if (!(displ->display = wl_display_connect(NULL))) {
		log_error("Unable to connect to the compositor. Check or set the WAYLAND_DISPLAY environment variable.");
		return false;
	}

	displ->registry = wl_display_get_registry(displ->display);

	wl_registry_add_listener(displ->registry, &listener, displ);

	if (wl_display_roundtrip(displ->display) == -1) {
		log_error("wl_display_roundtrip failed -1");
		return false;
	}

	if (!displ->layout_manager) {
		log_error("Compositor does not support river_layout_v3 protocol.");
		return false;
	}

	return true;
}
