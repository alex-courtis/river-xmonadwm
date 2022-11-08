#ifndef DISPL_H
#define DISPL_H

#include <stdbool.h>
#include <wayland-client-protocol.h>

#include "river-layout-v3-client-protocol.h"

extern struct Displ *displ;

struct Displ {
	// global singletons
	struct wl_display *wl_display;
	struct wl_registry *wl_registry;
	struct river_layout_manager_v3 *river_layout_manager;

	struct SList *outputs;

	// state
	bool terminate;
	int rc;
};

bool displ_init(void);

void displ_destroy(void);

#endif // DISPL_H
