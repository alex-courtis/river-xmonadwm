#ifndef LAYOUT_H
#define LAYOUT_H

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

// return a river layout name, caller frees
char *layout_description(const struct Demand demand, const struct Tag tag);

// populate views with Box for river layout push dimensions, caller frees
struct SList *layout(const struct Demand demand, const struct Tag tag);

#endif // LAYOUT_H

