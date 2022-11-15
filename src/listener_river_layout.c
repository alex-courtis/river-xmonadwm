#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "river-layout-v3-client-protocol.h"

#include "config.h"
#include "displ.h"
#include "layout.h"
#include "log.h"
#include "output.h"
#include "tag.h"

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
	if (!output)
		return;

	struct Tag *tag = tag_first(output->tags, tags);
	enum Layout layout = tag ? tag->layout_cur : config()->layout;

	push_views(layout, output->river_layout, view_count, usable_width, usable_height, serial);

	river_layout_v3_commit(output->river_layout, "[]=", serial);
}

static void layout_handle_namespace_in_use(void *data,
		struct river_layout_v3 *river_layout_v3) {
	log_error("river namespace in use, exiting");
	displ->terminate = true;
	displ->rc = EXIT_FAILURE;
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

