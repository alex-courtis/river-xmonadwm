#ifndef DISPL_H
#define DISPL_H

#include <stdbool.h>
#include <wayland-client-protocol.h>

#include "river-layout-v3-client-protocol.h"

struct Displ {
	// global
	struct wl_display *display;
	struct wl_registry *registry;
	uint32_t name;
	char *interface;

	// river
	struct river_layout_manager_v3 *layout_manager;
	struct SList *outputs;
};

bool displ_connect(void);

#endif // DISPL_H
