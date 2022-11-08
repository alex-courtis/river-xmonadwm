#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>

#include "tag.h"

struct river_layout_v3;

void push_view_dimensions(const enum Layout layout,
		struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial);

#endif // LAYOUT_H
