#include <stdlib.h>
#include <string.h>

#include "listeners.h"
#include "log.h"
#include "list.h"
#include "output.h"

#include "displ.h"

// Displ data

static void global(void *data,
		struct wl_registry *wl_registry,
		uint32_t name,
		const char *interface,
		uint32_t version) {
	log_debug("listener_registry global %lu %s %lu", name, interface, version);

	struct Displ *displ = data;

	if (strcmp(interface, river_layout_manager_v3_interface.name) == 0) {

		log_debug("listener_registry global     registering river layout manager");

		displ->layout_manager = wl_registry_bind(wl_registry, name, &river_layout_manager_v3_interface, version);

	} else if (strcmp(interface, wl_output_interface.name) == 0) {

		if (!displ->layout_manager) {
			log_error("Cannot create layout for output, missing river layout mananger.");
			return;
		}

		log_debug("listener_registry global     registering output");

		struct wl_output *wl_output = wl_registry_bind(wl_registry, name, &wl_output_interface, version);

		struct Output *output = output_init(wl_output, displ->layout_manager);
		if (output) {
			slist_append(&displ->outputs, output);
		}
	}
}

static void global_remove(void *data,
		struct wl_registry *wl_registry,
		uint32_t name) {
	// NOP: we end on failed wl_display_dispatch
}

static const struct wl_registry_listener listener = {
	.global = global,
	.global_remove = global_remove,
};

const struct wl_registry_listener *registry_listener(void) {
	return &listener;
}

