#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "arrange.h"

//
// asserts
//
static void _assert_boxes_equal(struct Box *a, struct Box *b,
		const char * const file, const int line) {
	if (!a) {
		print_error("Box a is null\n");
		_fail(file, line);
	}
	if (!b) {
		print_error("Box b is null\n");
		_fail(file, line);
	}
	if (memcmp(a, b, sizeof(struct Box)) != 0) {
		print_error("struct Box a = { .x = %d, .y = %d .width = %d, .height = %d, };\n"
				"struct Box b = { .x = %d, .y = %d .width = %d, .height = %d, };\n",
				a->x, a->y, a->width, a->height, b->x, b->y, b->width, b->height);
		_fail(file, line);
	}
}
#define assert_boxes_equal(a, b) _assert_boxes_equal(a, b, __FILE__, __LINE__)

#define assert_box_equal(a, x, y, width, height) \
{ \
	struct Box expected = { x, y, width, height, }; \
	_assert_boxes_equal(a, &expected, __FILE__, __LINE__); \
}

