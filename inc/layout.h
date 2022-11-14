#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdbool.h>
#include <stdint.h>

#include "tag.h"

struct river_layout_v3;

struct Box {
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
};

enum Ordinal {
	NE,
	SE,
	SW,
	NW,
};

void calc_master_stack(const enum Layout layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		struct Box *master,
		struct Box *stack);

void push_monocle(struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial);

void push_linear(struct river_layout_v3 *river_layout,
		const uint32_t stack_count,
		const struct Box usable,
		const bool left_to_right,
		const uint32_t serial);

void push_dwindle(struct river_layout_v3 *river_layout,
		const uint32_t stack_count,
		const struct Box usable,
		const enum Ordinal ordinal,
		const bool vertical,
		const uint32_t serial);

void push_views(const enum Layout layout,
		struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial);

#endif // LAYOUT_H
