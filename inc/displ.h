#ifndef DISPL_H
#define DISPL_H

#include <stdbool.h>

extern struct Displ displ;

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

// connect and register all listeners
bool displ_connect(void);

// disconnect the display, destroying resources
void displ_disconnect(void);

#endif // DISPL_H
