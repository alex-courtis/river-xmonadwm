#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arrange.h"
#include "config.h"
#include "tag.h"

#include "layout.h"

char *layout_description(const struct Demand demand, const struct Tag tag) {
	char *desc = calloc(16, sizeof(char));

	switch(tag.layout_cur) {
		case LEFT:
			snprintf(desc, 16, "┣━"); // "┃ ┣━┫"
			break;
		case RIGHT:
			snprintf(desc, 16, "━┫"); // "┣━┫ ┃"
			break;
		case TOP:
			snprintf(desc, 16, "━┻━"); // "┣━┻━┫"
			break;
		case BOTTOM:
			snprintf(desc, 16, "━┳━"); // "┣━┳━┫"
			break;
		case MONOCLE:
			snprintf(desc, 16, "┃%u┃", demand.view_count);
			break;
		case MID:
			snprintf(desc, 16, "━┫ ┣━"); // "┣━┫ ┣━┫"
			break;
		default:
			break;
	}

	return desc;
}

struct SList **layout(const struct Demand demand, const struct Tag tag) {
	struct SList **views = NULL;

	struct Box box_master = { 0 };
	struct Box box_stack = { 0 };

	uint32_t num_master = tag.count_master;
	uint32_t num_stack = demand.view_count - num_master;

	arrange_master_stack(demand, tag, &box_master, &box_stack);

	switch(tag.layout_cur) {
		case LEFT:
		case RIGHT:
			// top to bottom
			arrange_views(demand, EVEN, S, S, num_master, num_master, box_master, box_master, views);
			arrange_views(demand, tag.stack, S, S, num_stack, num_stack, box_stack, box_stack, views);
			break;
		case TOP:
		case BOTTOM:
			// left to right
			arrange_views(demand, EVEN, E, E, num_master, num_master, box_master, box_master, views);
			arrange_views(demand, tag.stack, E, E, num_stack, num_stack, box_stack, box_stack, views);
			break;
		case MONOCLE:
			arrange_monocle(demand, views);
			break;
		case MID:
			// top to bottom
			// TODO left stack
			arrange_views(demand, EVEN, S, S, num_master, num_master, box_master, box_master, views);
			arrange_views(demand, tag.stack, S, S, num_stack, num_stack, box_stack, box_stack, views);
			break;
	}

	return views;
}
