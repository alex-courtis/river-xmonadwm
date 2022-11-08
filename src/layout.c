#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "river_layout.h"
#include "tag.h"

#include "layout.h"

void push_stack_vertical(struct river_layout_v3 *river_layout,
		const uint32_t stack_count,
		const uint32_t x,
		const uint32_t width,
		const uint32_t usable_height,
		const uint32_t serial) {

	if (stack_count == 0)
		return;

	uint32_t height;
	uint32_t y;

	height = (usable_height + 1) / stack_count;

	y = 0;
	for (uint32_t i = 0; i < stack_count; i++) {
		if (i == stack_count - 1) {
			// bottom of stack takes remaining room to deal with rounding
			height = usable_height - y;
		}
		_river_layout_v3_push_view_dimensions(river_layout, x, y, width, height, serial);
		y += height;
	}
}

void push_layout_monocle(struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial) {
	for (uint32_t i = 0; i < view_count; i++) {
		_river_layout_v3_push_view_dimensions(river_layout, 0, 0, usable_width, usable_height, serial);
	}
}

void push_layout_lr(const bool left,
		struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial) {

	if (view_count == 0)
		return;

	int32_t x;
	uint32_t width;
	uint32_t height;

	// main left or right
	width = usable_width;
	if (view_count > 1) {
		width = (width + 1) / 2;
	}
	height = usable_height;
	if (left) {
		x = 0;
	} else {
		x = usable_width - width;
	}
	_river_layout_v3_push_view_dimensions(river_layout, x, 0, width, height, serial);

	// stack remaining
	if (left) {
		x = width;
	} else {
		x = 0;
	}
	push_stack_vertical(river_layout, view_count - 1, x, usable_width - width, usable_height, serial);
}

void push_view_dimensions(const enum Layout layout,
		struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial) {

	switch(layout) {
		case LAYOUT_LEFT:
		case LAYOUT_RIGHT:
			push_layout_lr(layout == LAYOUT_LEFT, river_layout, view_count, usable_width, usable_height, serial);
			break;
		case LAYOUT_MONOCLE:
		default:
			push_layout_monocle(river_layout, view_count, usable_width, usable_height, serial);
			break;
	}
}

