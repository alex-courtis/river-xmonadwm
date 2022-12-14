#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "layout.h"
#include "list.h"
#include "tag.h"

#include "arrange.h"

void arrange_master_stack(const struct Demand demand,
		const struct Tag tag,
		struct Box *master,
		struct Box *stack) {

	memset(master, 0, sizeof(*master));
	memset(stack, 0, sizeof(*master));

	if (tag.count_master <= 0) {
		stack->width = demand.usable_width;
		stack->height = demand.usable_height;
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

		case MONOCLE:
		case MID:
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

		case MONOCLE:
		case MID:
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

		case MONOCLE:
		case MID:
			break;
	}
}

void arrange_monocle(const struct Demand demand,
		struct SList **views) {

	struct Box usable = { 0, 0, demand.usable_width, demand.usable_height };

	for (uint32_t i = 0; i < demand.view_count; i++) {
		struct Box *this = calloc(1, sizeof(struct Box));
		memcpy(this, &usable, sizeof(struct Box));

		slist_append(views, this);
	}
}

void arrange_views(const struct Demand demand,
		const enum Stack stack,
		const enum Cardinal dir_cur,
		const enum Cardinal dir_next,
		const uint32_t num_total,
		const uint32_t num_remaining,
		const struct Box box_total,
		const struct Box box_remaining,
		struct SList **views) {
	if (num_total == 0 || num_remaining == 0)
		return;

	struct Box *this = calloc(1, sizeof(struct Box));
	memcpy(this, &box_remaining, sizeof(struct Box));

	if (num_remaining == 1) {
		slist_append(views, this);
		return;
	}

	// size
	uint32_t width, height, denom = 0;
	switch (stack) {
		case EVEN:
			width = (double)(box_remaining.width) / num_remaining + 0.5;
			height = (double)(box_remaining.height) / num_remaining + 0.5;
			break;
		case DIMINISH:
			for (uint32_t i = num_total; i > 0; i--)
				denom += i;
			width = (double)(num_remaining) * box_total.width / denom + 0.5;
			height = (double)(num_remaining) * box_total.height / denom + 0.5;
			break;
		case DWINDLE:
			width = (double)(box_remaining.width) / 2 + 0.5;
			height = (double)(box_remaining.height) / 2 + 0.5;
			break;
	}

	// dimension
	struct Box remaining = box_remaining;
	switch (dir_cur) {
		case N:
		case S:
			this->height = height;
			remaining.height -= this->height;
			break;
		case E:
		case W:
			this->width = width;
			remaining.width -= this->width;
			break;
	}

	// position
	switch (dir_cur) {
		case N:
			this->y += box_remaining.height - this->height;
			break;
		case S:
			remaining.y += this->height;
			break;
		case E:
			remaining.x += this->width;
			break;
		case W:
			this->x += box_remaining.width - this->width;
			break;
	}

	slist_append(views, this);

	arrange_views(demand, stack,
			stack == DWINDLE ? dir_next : dir_cur,
			stack == DWINDLE ? dir_cur : dir_next,
			num_total, num_remaining - 1,
			box_total, remaining,
			views);
}

