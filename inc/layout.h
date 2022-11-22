#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdbool.h>
#include <stdint.h>

#include "tag.h"

struct river_layout_v3;

struct Demand {
	struct river_layout_v3 *river_layout;
	const uint32_t view_count;
	const uint32_t usable_width;
	const uint32_t usable_height;
	const uint32_t tags;
	const uint32_t serial;
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

// populate master/stack areas for Tag
void calc_master_stack(const struct Demand demand,
		const struct Tag tag,
		struct Box *master,
		struct Box *stack);

// append many new Box to views with full usable area
void layout_monocle(const struct Demand demand,
		struct SList **views);

// recursively append new Box to views as per stack
void layout_view(const struct Demand demand,
		const enum Stack stack,
		const enum Cardinal dir_cur,
		const enum Cardinal dir_next,
		const uint32_t num_total,
		const uint32_t num_remaining,
		const struct Box box_total,
		const struct Box box_remaining,
		struct SList **views);

void push_views(const struct Demand demand,
		const struct Tag tag);

#endif // LAYOUT_H

