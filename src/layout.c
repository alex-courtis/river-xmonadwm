#include "layout.h"
#include "output.h"

void apply_view_dimensions(const struct Tag *tag,
		struct river_layout_v3 *river_layout,
		const uint32_t view_count,
		const uint32_t usable_width,
		const uint32_t usable_height,
		const uint32_t serial) {

	uint32_t x = 100;
	uint32_t y = 50;

	for (uint32_t i = 0; i < view_count; i++) {
		river_layout_v3_push_view_dimensions(river_layout,
				x,
				y,
				400,
				300,
				serial);

		x += 100;
		y += 50;
	}
}

