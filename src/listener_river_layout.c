#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "river-layout-v3-client-protocol.h"

#include "displ.h"
#include "layout.h"
#include "list.h"
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
	log_debug("layout_handle_layout_demand %u %ux%u 0x%ux", view_count, usable_width, usable_height, tags);

	struct Output *output = (struct Output*)data;
	if (!output)
		return;

	const struct Demand demand = {
		.view_count = view_count,
		.usable_width = usable_width,
		.usable_height = usable_height,
	};

	// use lowest tag's layout
	struct Tag *tag = tag_first(output->tags, tags);

	// position all views
	struct SList **views = layout(demand, *tag);

	// push all views
	for (struct SList *i = *views; i; i = i->nex) {
		struct Box *box = i->val;
		river_layout_v3_push_view_dimensions(river_layout_v3, box->x, box->y, box->width, box->height, serial);
	}
	slist_free_vals(views, NULL);

	// river name
	char *name = layout_description(demand, *tag);

	// commit
	river_layout_v3_commit(output->river_layout, name, serial);

	free(name);
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
	log_debug("layout_handle_user_command_tags 0x%ux", tags);
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

