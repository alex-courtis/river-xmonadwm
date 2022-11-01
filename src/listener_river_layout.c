#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "displ.h"
#include "log.h"
#include "list.h"

#include "output.h"

// Output data

static void layout_handle_layout_demand(void *data,
		struct river_layout_v3 *river_layout_v3,
		uint32_t view_count,
		uint32_t usable_width,
		uint32_t usable_height,
		uint32_t tags,
		uint32_t serial) {
	log_debug("layout_handle_layout_demand %lu %lux%lu 0x%lux", view_count, usable_width, usable_height, tags);

	struct Output *output = (struct Output*)data;

	uint32_t x = 100;
	uint32_t y = 50;

	for (uint32_t i = 0; i < view_count; i++) {
		river_layout_v3_push_view_dimensions(output->river_layout,
				x,
				y,
				400,
				300,
				serial);

		x += 100;
		y += 50;
	}

	river_layout_v3_commit(output->river_layout, "[]=", serial);
}

static void layout_handle_namespace_in_use(void *data,
		struct river_layout_v3 *river_layout_v3) {
	log_error("river namespace in use, exiting");
	displ->terminate = true;
}

static void layout_handle_user_command(void *data,
		struct river_layout_v3 *river_layout_manager_v3,
		const char *command) {
	log_debug("layout_handle_user_command '%s'", command);
}

static void layout_handle_user_command_tags(void *data,
		struct river_layout_v3 *river_layout_manager_v3,
		uint32_t tags) {
	log_debug("layout_handle_user_command_tags 0x%lux", tags);
}

static const struct river_layout_v3_listener listener = {
	.namespace_in_use = layout_handle_namespace_in_use,
	.layout_demand = layout_handle_layout_demand,
	.user_command = layout_handle_user_command,
	.user_command_tags = layout_handle_user_command_tags,
};

const struct river_layout_v3_listener *river_layout_listener(void) {
	return &listener;
}

