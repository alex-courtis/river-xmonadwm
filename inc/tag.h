#ifndef TAG_H
#define TAG_H

#include <stdint.h>

enum Layout {
	LAYOUT_MONOCLE,
	LAYOUT_LEFT,
	LAYOUT_RIGHT,
	LAYOUT_MID,
	LAYOUT_DEFAULT = LAYOUT_LEFT,
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

