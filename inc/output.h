#ifndef LAYOUT_H
#define LAYOUT_H

#include "river-layout-v3-client-protocol.h"

struct Output {
	struct wl_output *output;
	struct river_layout_v3 *layout;
};

#endif // LAYOUT_H
