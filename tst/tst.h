#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "layout.h"

struct river_layout_v3;

//
// private types
//
struct Box {
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
};

enum Ordinal {
	NE,
	SE,
	SW,
	NW,
};

//
// private prototypes
//
void calc_master_stack(const struct Demand demand, const struct Tag tag, struct Box *master, struct Box *stack);

void push_monocle(const struct Demand demand);

void push_linear(const struct Demand demand, const struct Tag tag, const uint32_t stack_count, const struct Box usable, const bool left_to_right);

void push_dwindle(const struct Demand demand, const struct Tag tag, const uint32_t stack_count, const struct Box usable, const enum Ordinal ordinal, const bool vertical);

//
// wrappers
//
void __wrap__river_layout_v3_push_view_dimensions(struct river_layout_v3 *river_layout_v3, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t serial) {
	check_expected(x);
	check_expected(y);
	check_expected(width);
	check_expected(height);
}

//
// expectations
//
#define expect_river_push_view_dimensions(X, Y, WIDTH, HEIGHT) \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, x, X); \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, y, Y); \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, width, WIDTH); \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, height, HEIGHT)

//
// asserts
//
static void _assert_box_equal(struct Box *a, struct Box *b,
		const char * const file, const int line) {
	if (memcmp(a, b, sizeof(struct Box)) != 0) {
		print_error("struct Box a = { .x = %d, .y = %d .width = %d, .height = %d, };\n"
				"struct Box b = { .x = %d, .y = %d .width = %d, .height = %d, };\n",
				a->x, a->y, a->width, a->height, b->x, b->y, b->width, b->height);
		_fail(file, line);
	}
}
#define assert_box_equal(a, b) _assert_box_equal(a, b, __FILE__, __LINE__)

