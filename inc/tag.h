#ifndef TAG_H
#define TAG_H

#include <stdint.h>

#include "config.h"

struct Tag {
	uint32_t mask;
	enum Layout layout_cur;
	enum Layout layout_prev;
	uint32_t count_master;
	double ratio_master;
	double ratio_stack;
};

struct Tag *tag_init(const uint32_t mask);

struct SList *tags_init(void);

void tag_destroy(void *t);

void tags_destroy(struct SList *tags);

// return the first tag that fits mask otherwise first
struct Tag *tag_first(struct SList *tags, const uint32_t mask);

#endif // TAG_H

