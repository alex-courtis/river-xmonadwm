#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "river_layout.h"
#include "tag.h"

#include "layout.h"

void calc_master_stack(const struct Demand demand, const struct Tag tag, struct Box *master, struct Box *stack) {

	memset(master, 0, sizeof(*master));
	memset(stack, 0, sizeof(*master));

	if (demand.view_count == 0) {
		return;
	}

	if (tag.count_master >= demand.view_count) {
		master->width = demand.usable_width;
		master->height = demand.usable_height;
		return;
	}

	// size
	switch(tag.layout_cur) {
		case LEFT:
		case RIGHT:
			master->width = (demand.usable_width + 1) * tag.ratio_master;
			master->height = demand.usable_height;
			stack->width = demand.usable_width - master->width;
			stack->height = demand.usable_height;
			break;

		case TOP:
		case BOTTOM:
			master->width = demand.usable_width;
			master->height = (demand.usable_height + 1) * tag.ratio_master;
			stack->width = demand.usable_width;
			stack->height = demand.usable_height - master->height;
			break;

		default:
			break;
	}

	// master position
	switch(tag.layout_cur) {
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
	switch(tag.layout_cur) {
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

void push_stack(const struct Demand demand,
		const enum Stack mode,
		const enum Cardinal dir_cur,
		const enum Cardinal dir_next,
		const uint32_t num_total,
		const uint32_t num_remaining,
		const struct Box box_total,
		const struct Box box_stack) {
	if (num_total == 0 || num_remaining == 0)
		return;

	if (num_remaining == 1) {
		_river_layout_v3_push_view_dimensions(demand.river_layout, box_stack.x, box_stack.y, box_stack.width, box_stack.height, demand.serial);
		return;
	}

	// size
	uint32_t width, height, denom = 0;
	switch (mode) {
		case EVEN:
			width = (double)(box_total.width) / num_total + 0.5;
			height = (double)(box_total.height) / num_total + 0.5;
			break;
		case DIMINISH:
			for (uint32_t i = num_total; i > 0; i--)
				denom += i;
			width = (double)(num_remaining) * box_total.width / denom + 0.5;
			height = (double)(num_remaining) * box_total.height / denom + 0.5;
			break;
		case DWINDLE:
			width = (double)(box_stack.width) / 2 + 0.5;
			height = (double)(box_stack.height) / 2 + 0.5;
			break;
	}

	// dimension
	struct Box this = box_stack;
	struct Box remaining = box_stack;
	switch (dir_cur) {
		case N:
		case S:
			this.height = height;
			remaining.height -= this.height;
			break;
		case E:
		case W:
			this.width = width;
			remaining.width -= this.width;
			break;
	}

	// position
	switch (dir_cur) {
		case N:
			this.y += box_stack.height - this.height;
			break;
		case S:
			remaining.y += this.height;
			break;
		case E:
			remaining.x += this.width;
			break;
		case W:
			this.x += box_stack.width - this.width;
			break;
	}

	_river_layout_v3_push_view_dimensions(demand.river_layout, this.x, this.y, this.width, this.height, demand.serial);

	if (mode == DWINDLE) {
		push_stack(demand, mode, dir_next, dir_cur, num_total, num_remaining - 1, box_total, remaining);
	} else {
		push_stack(demand, mode, dir_cur, dir_next, num_total, num_remaining - 1, box_total, remaining);
	}
}

void push_views(const struct Demand demand, const struct Tag tag) {

	struct Box master = { 0 };
	struct Box stack = { 0 };

	calc_master_stack(demand, tag, &master, &stack);

	switch(tag.layout_cur) {
		case LEFT:
		case RIGHT:
			// top to bottom
			push_stack(demand, tag.stack, S, S, tag.count_master, tag.count_master, master, master);
			push_stack(demand, tag.stack, S, S, demand.view_count, demand.view_count, stack, stack);
			break;
		case TOP:
		case BOTTOM:
			// left to right
			push_stack(demand, tag.stack, E, E, tag.count_master, tag.count_master, master, master);
			push_stack(demand, tag.stack, E, E, demand.view_count, demand.view_count, stack, stack);
			break;
		case MONOCLE:
			push_monocle(demand);
			break;
		case MID:
			break;
	}
}

