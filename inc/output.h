#ifndef OUTPUT_H
#define OUTPUT_H

#include <wayland-client-protocol.h>

#include "river-layout-v3-client-protocol.h"

struct Output {
	struct wl_output *wl_output;
	struct river_layout_v3 *river_layout;
};

struct Output *output_init(struct wl_output *wl_output, struct river_layout_manager_v3 *river_layout_manager);

void output_destroy(struct Output *output);

#endif // OUTPUT_H
