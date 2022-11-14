#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "river_layout.h"
#include "tag.h"

#include "layout.h"

void calc_master_stack(const enum Layout layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		struct Box *master,
		struct Box *stack) {

	memset(master, 0, sizeof(*master));
	memset(stack, 0, sizeof(*master));

	switch (view_count) {
		case 0:
			return;
		case 1:
			master->width = usable_width;
			master->height = usable_height;
			return;
		default:
			break;
	}

	// size
	switch(layout) {
		case LAYOUT_LEFT:
		case LAYOUT_RIGHT:
			master->width = (usable_width + 1) / 2;
			master->height = usable_height;
			stack->width = usable_width - master->width;
			stack->height = usable_height;
			break;

		case LAYOUT_TOP:
		case LAYOUT_BOTTOM:
			master->width = usable_width;
			master->height = (usable_height + 1) / 2;
			stack->width = usable_width;
			stack->height = usable_height - master->height;
			break;

		default:
			break;
	}

	// master position
	switch(layout) {
		case LAYOUT_LEFT:
		case LAYOUT_TOP:
			master->x = 0;
			master->y = 0;
			break;

		case LAYOUT_RIGHT:
			master->x = usable_width - master->width;
			master->y = 0;
			break;

		case LAYOUT_BOTTOM:
			master->x = 0;
			master->y = master->height;
			break;

		default:
			break;
	}

	// stack position
	switch(layout) {
		case LAYOUT_LEFT:
			stack->x = master->width;
			stack->y = 0;
			break;

		case LAYOUT_TOP:
			stack->x = 0;
			stack->y = master->height;
			break;

		case LAYOUT_RIGHT:
		case LAYOUT_BOTTOM:
			stack->x = 0;
			stack->y = 0;
			break;

		default:
			break;
	}
}

void push_monocle(struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial) {
	for (uint32_t i = 0; i < view_count; i++) {
		_river_layout_v3_push_view_dimensions(river_layout, 0, 0, usable_width, usable_height, serial);
	}
}

void push_linear(struct river_layout_v3 *river_layout,
		const uint32_t stack_count,
		const struct Box usable,
		const bool left_to_right,
		const uint32_t serial) {

	if (stack_count == 0)
		return;

	uint32_t x = usable.x;
	uint32_t y = usable.y;
	uint32_t width;
	uint32_t height;

	if (left_to_right) {
		width = (usable.width + 1) / stack_count;
		height = usable.height;
	} else {
		width = usable.width;
		height = (usable.height + 1) / stack_count;
	}

	for (uint32_t i = 0; i < stack_count - 1; i++) {
		if (i == stack_count - 1) {
			height = usable.height + usable.y - y;
		}

		_river_layout_v3_push_view_dimensions(river_layout, x, y, width, height, serial);

		if (left_to_right) {
			x += width;
		} else {
			y += height;
		}
	}

	// bottom of stack takes remaining room to deal with rounding
	if (left_to_right) {
		width = usable.width + usable.x - x;
	} else {
		height = usable.height + usable.y - y;
	}

	_river_layout_v3_push_view_dimensions(river_layout, x, y, width, height, serial);
}

void push_dwindle(struct river_layout_v3 *river_layout,
		const uint32_t stack_count,
		const struct Box usable,
		const enum Ordinal ordinal,
		const bool vertical,
		const uint32_t serial) {

	if (stack_count == 0) {
		return;
	} else if (stack_count == 1) {
		_river_layout_v3_push_view_dimensions(river_layout, usable.x, usable.y, usable.width, usable.height, serial);
		return;
	}

	struct Box this = usable;
	struct Box remaining = usable;

	if (vertical) {
		this.height = (usable.height + 1) / 2;
		switch (ordinal) {
			case NE:
			case NW:
				this.y += usable.height - this.height;
				remaining.height -= this.height;
				break;
			case SE:
			case SW:
				remaining.y += this.height;
				remaining.height -= this.height;
				break;
		}
	} else {
		this.width = (usable.width + 1) / 2;
		switch (ordinal) {
			case SW:
			case NW:
				this.x += usable.width - this.width;
				remaining.width -= this.width;
				break;
			case NE:
			case SE:
				remaining.x += this.width;
				remaining.width -= this.width;
				break;
		}
	}

	_river_layout_v3_push_view_dimensions(river_layout, this.x, this.y, this.width, this.height, serial);

	push_dwindle(river_layout, stack_count - 1, remaining, ordinal, !vertical, serial);
}

void push_views(const enum Layout layout,
		struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial) {

	struct Box master = { 0 };
	struct Box stack = { 0 };

	calc_master_stack(layout, view_count, usable_width, usable_height, &master, &stack);

	switch(layout) {
		case LAYOUT_LEFT:
		case LAYOUT_RIGHT:
			// top to bottom
			push_linear(river_layout, 1, master, false, serial);
			push_linear(river_layout, view_count - 1, stack, false, serial);
			break;
		case LAYOUT_TOP:
		case LAYOUT_BOTTOM:
			// left to right
			push_linear(river_layout, 1, master, true, serial);
			push_linear(river_layout, view_count - 1, stack, true, serial);
			break;
		case LAYOUT_MONOCLE:
			push_monocle(river_layout, view_count, usable_width, usable_height, serial);
			break;
		case LAYOUT_MID:
			break;
	}
}

