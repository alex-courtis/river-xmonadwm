#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arrange.h"
#include "config.h"
#include "log.h"
#include "tag.h"

#include "layout.h"

char *layout_description(const struct Demand demand, const struct Tag tag) {
	char *desc = calloc(16, sizeof(char));

	switch(tag.layout_cur) {
		case LEFT:
			snprintf(desc, 16, " ┣━"); // "┃ ┣━┫"
			break;
		case RIGHT:
			snprintf(desc, 16, "━┫ "); // "┣━┫ ┃"
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
	}

	return desc;
}

struct SList *layout(const struct Demand demand, const struct Tag tag) {
	struct SList *views = NULL;

	struct Box box_master = { 0 };
	struct Box box_stack = { 0 };

	arrange_master_stack(demand, tag, &box_master, &box_stack);
	log_debug("master: %u,%u %ux%u", box_master.x, box_master.y, box_master.width, box_master.height);
	log_debug("stack:  %u,%u %ux%u", box_stack.x, box_stack.y, box_stack.width, box_stack.height);

	uint32_t num_master = tag.count_master;
	uint32_t num_stack = demand.view_count - num_master;

	switch(tag.layout_cur) {
		case LEFT:
			// top to bottom, dwindle right
			arrange_views(demand, EVEN, S, S, num_master, num_master, box_master, box_master, &views);
			arrange_views(demand, tag.stack, S, E, num_stack, num_stack, box_stack, box_stack, &views);
			break;
		case RIGHT:
			// top to bottom, dwindle left
			arrange_views(demand, EVEN, S, S, num_master, num_master, box_master, box_master, &views);
			arrange_views(demand, tag.stack, S, W, num_stack, num_stack, box_stack, box_stack, &views);
			break;
		case TOP:
			// left to right, dwindle down
			arrange_views(demand, EVEN, E, E, num_master, num_master, box_master, box_master, &views);
			arrange_views(demand, tag.stack, E, S, num_stack, num_stack, box_stack, box_stack, &views);
			break;
		case BOTTOM:
			// left to right, dwindle up
			arrange_views(demand, EVEN, E, E, num_master, num_master, box_master, box_master, &views);
			arrange_views(demand, tag.stack, E, N, num_stack, num_stack, box_stack, box_stack, &views);
			break;
		case MONOCLE:
			arrange_monocle(demand, &views);
			break;
		case MID:
			// top to bottom
			// TODO left stack
			arrange_views(demand, EVEN, S, S, num_master, num_master, box_master, box_master, &views);
			arrange_views(demand, tag.stack, S, S, num_stack, num_stack, box_stack, box_stack, &views);
			break;
	}

	return views;
}
