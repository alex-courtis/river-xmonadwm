#ifndef ARRANGE_H
#define ARRANGE_H

#include <stdint.h>

#include "config.h"
#include "layout.h"
#include "list.h"
#include "tag.h"

enum Cardinal {
	N,
	S,
	E,
	W,
};

// populate master/stack areas for Tag
void arrange_master_stack(const struct Demand demand,
		const struct Tag tag,
		struct Box *master,
		struct Box *stack);

// append many new Box to views with full usable area
void arrange_monocle(const struct Demand demand,
		struct SList **views);

// recursively append new Box to views as per stack
void arrange_views(const struct Demand demand,
		const enum Stack stack,
		const enum Cardinal dir_cur,
		const enum Cardinal dir_next,
		const uint32_t num_total,
		const uint32_t num_remaining,
		const struct Box box_total,
		const struct Box box_remaining,
		struct SList **views);

#endif // ARRANGE_H

