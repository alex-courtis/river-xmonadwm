#include <stdint.h>
#include <wayland-client-protocol.h>

#include "river-layout-v3-client-protocol.h"

void _river_layout_manager_v3_destroy(struct river_layout_manager_v3 *river_layout_manager_v3) {
	river_layout_manager_v3_destroy(river_layout_manager_v3);
}

int _river_layout_v3_add_listener(struct river_layout_v3 *river_layout_v3, const struct river_layout_v3_listener *listener, void *data) {
	return river_layout_v3_add_listener(river_layout_v3, listener, data);
}

struct river_layout_v3 *_river_layout_manager_v3_get_layout(struct river_layout_manager_v3 *river_layout_manager_v3, struct wl_output *output, const char *namespace) {
	return river_layout_manager_v3_get_layout(river_layout_manager_v3, output, namespace);
}

void _river_layout_v3_destroy(struct river_layout_v3 *river_layout_v3) {
	river_layout_v3_destroy(river_layout_v3);
}

void _river_layout_v3_push_view_dimensions(struct river_layout_v3 *river_layout_v3, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t serial) {
	river_layout_v3_push_view_dimensions(river_layout_v3, x, y, width, height, serial);
}

void _river_layout_v3_commit(struct river_layout_v3 *river_layout_v3, const char *layout_name, uint32_t serial) {
	river_layout_v3_commit(river_layout_v3, layout_name, serial);
}

