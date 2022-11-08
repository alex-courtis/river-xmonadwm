#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wayland-client-protocol.h>

#include "listeners.h"
#include "log.h"
#include "river_layout.h"
#include "tag.h"

#include "output.h"

struct Output *output_init(struct wl_output *wl_output, uint32_t name, struct river_layout_manager_v3 *river_layout_manager) {
	if (!wl_output) {
		log_warn("Cannot create output, missing wayland output.");
		return NULL;
	}
	if (!river_layout_manager) {
		log_warn("Cannot create output, missing river layout manager.");
		return NULL;
	}

	struct river_layout_v3 *river_layout = _river_layout_manager_v3_get_layout(river_layout_manager, wl_output, "river-xmonadwm");
	if (!river_layout) {
		log_warn("Failed to create river layout, ignoring output.");
		return NULL;
	}

	struct Output *output = calloc(1, sizeof(struct Output));
	output->wl_output = wl_output;
	output->name = name;
	output->river_layout = river_layout;
	output->tags = tags_init();

	_river_layout_v3_add_listener(river_layout, river_layout_listener(), output);

	return output;
}

void output_destroy(void *o) {
	if (!o)
		return;

	struct Output *output = o;

	if (output->river_layout) {
		_river_layout_v3_destroy(output->river_layout);
	}
	if (output->wl_output) {
		wl_output_destroy(output->wl_output);
	}
	if (output->tags) {
		tags_destroy(output->tags);
	}

	free(output);
}

