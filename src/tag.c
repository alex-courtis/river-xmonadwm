#include <stdint.h>
#include <stdlib.h>

#include "config.h"
#include "list.h"

#include "tag.h"

struct Tag *tag_init(const uint32_t mask) {
	struct Tag *tag = calloc(1, sizeof(struct Tag));

	tag->layout_cur = config()->layout;
	tag->layout_prev = config()->layout;
	tag->count_master = config()->count_master;
	tag->ratio_master = config()->ratio_master;
	tag->ratio_stack = config()->ratio_stack;

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

void tag_destroy(void *t) {
	if (!t)
		return;

	free(t);
}

void tags_destroy(struct SList *tags) {
	if (!tags)
		return;

	slist_free_vals(&tags, tag_destroy);
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

