#ifndef _RIVER_LAYOUT_V3_CLIENT_PROTOCOL_H
#define _RIVER_LAYOUT_V3_CLIENT_PROTOCOL_H

#include <stdint.h>

#include <wayland-client-protocol.h>

// forward declarations and wrapped inlines to allow mocking

struct river_layout_v3_listener;
struct river_layout_manager_v3;
struct river_layout_v3;

int _river_layout_v3_add_listener(struct river_layout_v3 *river_layout_v3, const struct river_layout_v3_listener *listener, void *data);

struct river_layout_v3 *_river_layout_manager_v3_get_layout(struct river_layout_manager_v3 *river_layout_manager_v3, struct wl_output *output, const char *namespace);

void _river_layout_manager_v3_destroy(struct river_layout_manager_v3 *river_layout_manager_v3);

void _river_layout_v3_destroy(struct river_layout_v3 *river_layout_v3);

void _river_layout_v3_push_view_dimensions(struct river_layout_v3 *river_layout_v3, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t serial);

void _river_layout_v3_commit(struct river_layout_v3 *river_layout_v3, const char *layout_name, uint32_t serial);

#endif // _RIVER_LAYOUT_V3_CLIENT_PROTOCOL_H

