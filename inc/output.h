#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>

struct river_layout_manager_v3;

struct Output {
	struct wl_output *wl_output;
	uint32_t name;
	struct river_layout_v3 *river_layout;
	struct SList *tags;
};

struct Output *output_init(struct wl_output *wl_output, uint32_t name, struct river_layout_manager_v3 *river_layout_manager);

void output_destroy(void *o);

#endif // OUTPUT_H
