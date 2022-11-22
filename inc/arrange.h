#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdbool.h>
#include <stdint.h>

#include "tag.h"

struct Demand {
	const uint32_t view_count;
	const uint32_t usable_width;
	const uint32_t usable_height;
};

struct Box {
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
};

enum Cardinal {
	N,
	S,
	E,
	W,
};

// populate views with Box for river layout push dimensions
struct SList **layout(const struct Demand demand,
		const struct Tag tag);

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

#endif // LAYOUT_H

