#include <stdint.h>
#include <stdlib.h>

#include "config.h"
#include "list.h"

#include "tag.h"

struct Tag *tag_init(const uint32_t mask) {
	struct Tag *tag = calloc(1, sizeof(struct Tag));

	tag->layout_cur = cfg.layout;
	tag->layout_prev = cfg.layout;

	tag->stack = cfg.stack;

	tag->count_master = cfg.count_master;
	tag->ratio_master = cfg.ratio_master;

	tag->mask = mask;

	return tag;
}

struct SList *tags_init(void) {
	struct SList *tags = NULL;

	// tag for all 32 bits of the uint32_t masks
	for (int i = 0; i < 32; i++) {
		slist_append(&tags, tag_init(1LL << i));
	}

	return tags;
}

void tags_destroy(struct SList *tags) {
	if (!tags)
		return;

	slist_free_vals(&tags, NULL);
}

struct Tag *tag_first(struct SList *tags, const uint32_t mask) {
	if (!tags) {
		return NULL;
	}

	for (struct SList *i = tags; i; i = i->nex) {
		struct Tag *tag = i->val;
		if (mask & tag->mask) {
			return i->val;
		}
	}

	// default to first
	return tags->val;
}

