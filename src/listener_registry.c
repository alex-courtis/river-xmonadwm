#include <stdint.h>
#include <string.h>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include "river-layout-v3-client-protocol.h"

#include "displ.h"
#include "list.h"
#include "log.h"
#include "output.h"

#include "listeners.h"

// Displ data

static void global(void *data,
		struct wl_registry *wl_registry,
		uint32_t name,
		const char *interface,
		uint32_t version) {
	log_debug("listener_registry global %lu %s %lu", name, interface, version);

	if (strcmp(interface, river_layout_manager_v3_interface.name) == 0) {

		log_debug("listener_registry global  registering river layout manager");

		if (version <= RIVER_LAYOUT_V3_VERSION) {
			displ->river_layout_manager = wl_registry_bind(wl_registry, name, &river_layout_manager_v3_interface, RIVER_LAYOUT_V3_VERSION);
		} else {
			log_error("Invalid river_layout_manager_v3_interface version %d expected %d, exiting", version, RIVER_LAYOUT_V3_VERSION);
			return;
		}

	} else if (strcmp(interface, wl_output_interface.name) == 0) {

		if (!displ->river_layout_manager) {
			log_error("Cannot create layout for output, missing river layout mananger, exiting");
			return;
		}

		log_debug("listener_registry global  registering output");

		struct wl_output *wl_output = wl_registry_bind(wl_registry, name, &wl_output_interface, version);

		struct Output *output = output_init(wl_output, name, displ->river_layout_manager);
		if (output) {
			slist_append(&displ->outputs, output);
		}
	}
}

static void global_remove(void *data,
		struct wl_registry *wl_registry,
		uint32_t name) {
	log_debug("listener_registry global_remove %lu", name);

	for (struct SList *i = displ->outputs; i; i = i->nex) {
		struct Output *output = i->val;
		if (output->name == name) {
			log_debug("listener_registry global  removing output");

			output_destroy(output);

			slist_remove(&displ->outputs, &i);

			break;
		}
	}
}

static const struct wl_registry_listener listener = {
	.global = global,
	.global_remove = global_remove,
};

const struct wl_registry_listener *registry_listener(void) {
	return &listener;
}

