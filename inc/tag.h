#ifndef TAG_H
#define TAG_H

#include <stdint.h>

enum Layout {
	LAYOUT_MONOCLE,
	LAYOUT_LEFT,
	LAYOUT_RIGHT,
	LAYOUT_TOP,
	LAYOUT_BOTTOM,
	LAYOUT_MID,
	LAYOUT_DEFAULT = LAYOUT_LEFT,
};

enum LayoutStack {
	LAYOUT_STACK_LINEAR,
	LAYOUT_STACK_DWINDLE,
	LAYOUT_STACK_DEFAULT = LAYOUT_STACK_LINEAR,
};

struct Tag {
	uint32_t mask;
	enum Layout layout;
};

struct SList *tags_init(void);

void tag_destroy(void *t);

void tags_destroy(struct SList *tags);

// return the first tag that fits mask otherwise first
struct Tag *tag_first(struct SList *tags, const uint32_t mask);

#endif // TAG_H

