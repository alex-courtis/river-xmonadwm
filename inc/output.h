#ifndef OUTPUT_H
#define OUTPUT_H

#include "river-layout-v3-client-protocol.h"

struct Output {
	struct wl_output *output;
	struct river_layout_v3 *layout;
};

#endif // OUTPUT_H
