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

void push_views(const struct Demand demand, const struct Tag *tag);

#endif // LAYOUT_H

