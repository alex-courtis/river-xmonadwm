#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>

#include "river-layout-v3-client-protocol.h"

#include "tag.h"

void lt(void);

void apply_view_dimensions(const struct Tag *tag,
		struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial);

#endif // LAYOUT_H
