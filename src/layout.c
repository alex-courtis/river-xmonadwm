#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "config.h"
#include "river_layout.h"
#include "tag.h"

#include "layout.h"

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

void calc_master_stack(const struct Demand demand, const struct Tag *tag, struct Box *master, struct Box *stack) {

	memset(master, 0, sizeof(*master));
	memset(stack, 0, sizeof(*master));

	if (demand.view_count == 0) {
		return;
	}

	if (tag->count_master >= demand.view_count) {
		master->width = demand.usable_width;
		master->height = demand.usable_height;
		return;
	}

	// size
	switch(tag->layout_cur) {
		case LEFT:
		case RIGHT:
			master->width = (demand.usable_width + 1) / 2;
			master->height = demand.usable_height;
			stack->width = demand.usable_width - master->width;
			stack->height = demand.usable_height;
			break;

		case TOP:
		case BOTTOM:
			master->width = demand.usable_width;
			master->height = (demand.usable_height + 1) / 2;
			stack->width = demand.usable_width;
			stack->height = demand.usable_height - master->height;
			break;

		default:
			break;
	}

	// master position
	switch(tag->layout_cur) {
		case LEFT:
		case TOP:
			master->x = 0;
			master->y = 0;
			break;

		case RIGHT:
			master->x = demand.usable_width - master->width;
			master->y = 0;
			break;

		case BOTTOM:
			master->x = 0;
			master->y = master->height;
			break;

		default:
			break;
	}

	// stack position
	switch(tag->layout_cur) {
		case LEFT:
			stack->x = master->width;
			stack->y = 0;
			break;

		case TOP:
			stack->x = 0;
			stack->y = master->height;
			break;

		case RIGHT:
		case BOTTOM:
			stack->x = 0;
			stack->y = 0;
			break;

		default:
			break;
	}
}

void push_monocle(const struct Demand demand) {
	for (uint32_t i = 0; i < demand.view_count; i++) {
		_river_layout_v3_push_view_dimensions(demand.river_layout, 0, 0, demand.usable_width, demand.usable_height, demand.serial);
	}
}

void push_linear(const struct Demand demand, const uint32_t stack_count, const struct Box usable, const bool left_to_right) {

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

		_river_layout_v3_push_view_dimensions(demand.river_layout, x, y, width, height, demand.serial);

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

	_river_layout_v3_push_view_dimensions(demand.river_layout, x, y, width, height, demand.serial);
}

void push_dwindle(const struct Demand demand, const uint32_t stack_count, const struct Box usable, const enum Ordinal ordinal, const bool vertical) {

	if (stack_count == 0) {
		return;
	} else if (stack_count == 1) {
		_river_layout_v3_push_view_dimensions(demand.river_layout, usable.x, usable.y, usable.width, usable.height, demand.serial);
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

	_river_layout_v3_push_view_dimensions(demand.river_layout, this.x, this.y, this.width, this.height, demand.serial);

	push_dwindle(demand, stack_count - 1, remaining, ordinal, !vertical);
}

void push_views(const struct Demand demand, const struct Tag *tag) {

	struct Box master = { 0 };
	struct Box stack = { 0 };

	calc_master_stack(demand, tag, &master, &stack);

	switch(tag->layout_cur) {
		case LEFT:
		case RIGHT:
			// top to bottom
			push_linear(demand, 1, master, false);
			push_linear(demand, demand.view_count - 1, stack, false);
			break;
		case TOP:
		case BOTTOM:
			// left to right
			push_linear(demand, 1, master, true);
			push_linear(demand, demand.view_count - 1, stack, true);
			break;
		case MONOCLE:
			push_monocle(demand);
			break;
		case MID:
			break;
	}
}

