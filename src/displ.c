#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>

#include "river-layout-v3-client-protocol.h"

#include "list.h"
#include "listeners.h"
#include "log.h"
#include "output.h"

#include "displ.h"

struct Displ displ = { 0 };

bool displ_connect(void) {
	memset(&displ, 0, sizeof(displ));

	displ.wl_display = wl_display_connect(NULL);
	if (!displ.wl_display) {
		log_error("Unable to connect to the compositor. Check or set the WAYLAND_DISPLAY environment variable.");
		return false;
	}

	displ.wl_registry = wl_display_get_registry(displ.wl_display);
	if (!displ.wl_registry) {
		log_error("wl_display_get_registry failed, exiting");
		return false;
	}

	wl_registry_add_listener(displ.wl_registry, registry_listener(), &displ);

	if (wl_display_roundtrip(displ.wl_display) == -1) {
		log_error("wl_display_roundtrip failed, exiting");
		return false;
	}

	if (!displ.river_layout_manager) {
		log_error("Compositor does not support river_layout_v3 protocol, exiting");
		return false;
	}

	return true;
}

void displ_disconnect(void) {
	slist_free_vals(&displ.outputs, output_destroy);

	if (displ.river_layout_manager) {
		river_layout_manager_v3_destroy(displ.river_layout_manager);
	}
	if (displ.wl_registry) {
		wl_registry_destroy(displ.wl_registry);
	}
	if (displ.wl_display) {
		wl_display_disconnect(displ.wl_display);
	}

	memset(&displ, 0, sizeof(displ));
}

