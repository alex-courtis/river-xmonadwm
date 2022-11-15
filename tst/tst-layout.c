#include <setjmp.h>  // IWYU pragma: keep
#include <stdarg.h>  // IWYU pragma: keep
#include <stddef.h>  // IWYU pragma: keep
#include <stdbool.h>
#include <stdint.h>

#include <cmocka.h>

#include "config.h"

#include "layout.h"

int setup(void **state) {
	return 0;
}

int teardown(void **state) {
	return 0;
}

#define expect_river_push_view_dimensions(X, Y, WIDTH, HEIGHT) \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, x, X); \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, y, Y); \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, width, WIDTH); \
	expect_value(__wrap__river_layout_v3_push_view_dimensions, height, HEIGHT);

void __wrap__river_layout_v3_push_view_dimensions(struct river_layout_v3 *river_layout_v3, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t serial) {
	check_expected(x);
	check_expected(y);
	check_expected(width);
	check_expected(height);
}

void push_monocle__zero(void **state) {
	push_monocle(NULL, 0, 9, 5, 999);
}

void push_monocle__one(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);

	push_monocle(NULL, 1, 9, 5, 999);
}

void push_monocle__many(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);
	expect_river_push_view_dimensions(0, 0, 9, 5);
	expect_river_push_view_dimensions(0, 0, 9, 5);

	push_monocle(NULL, 3, 9, 5, 999);
}

void calc_master_stack__zero(void **state) {
	struct Box master, stack;

	calc_master_stack(LEFT, 0, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 0);
	assert_int_equal(master.height, 0);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 0);
	assert_int_equal(stack.height, 0);
}

void calc_master_stack__left_one(void **state) {
	struct Box master, stack;

	calc_master_stack(LEFT, 1, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 9);
	assert_int_equal(master.height, 5);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 0);
	assert_int_equal(stack.height, 0);
}

void calc_master_stack__left_many(void **state) {
	struct Box master, stack;

	calc_master_stack(LEFT, 2, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 5);
	assert_int_equal(master.height, 5);

	assert_int_equal(stack.x, 5);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 4);
	assert_int_equal(stack.height, 5);
}

void calc_master_stack__right_one(void **state) {
	struct Box master, stack;

	calc_master_stack(RIGHT, 1, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 9);
	assert_int_equal(master.height, 5);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 0);
	assert_int_equal(stack.height, 0);
}

void calc_master_stack__right_many(void **state) {
	struct Box master, stack;

	calc_master_stack(RIGHT, 2, 9, 5, &master, &stack);

	assert_int_equal(master.x, 4);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 5);
	assert_int_equal(master.height, 5);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 4);
	assert_int_equal(stack.height, 5);
}

void calc_master_stack__top_one(void **state) {
	struct Box master, stack;

	calc_master_stack(TOP, 1, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 9);
	assert_int_equal(master.height, 5);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 0);
	assert_int_equal(stack.height, 0);
}

void calc_master_stack__top_many(void **state) {
	struct Box master, stack;

	calc_master_stack(TOP, 2, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 9);
	assert_int_equal(master.height, 3);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 3);
	assert_int_equal(stack.width, 9);
	assert_int_equal(stack.height, 2);
}

void calc_master_stack__bottom_one(void **state) {
	struct Box master, stack;

	calc_master_stack(BOTTOM, 1, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 0);
	assert_int_equal(master.width, 9);
	assert_int_equal(master.height, 5);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 0);
	assert_int_equal(stack.height, 0);
}

void calc_master_stack__bottom_many(void **state) {
	struct Box master, stack;

	calc_master_stack(BOTTOM, 2, 9, 5, &master, &stack);

	assert_int_equal(master.x, 0);
	assert_int_equal(master.y, 3);
	assert_int_equal(master.width, 9);
	assert_int_equal(master.height, 3);

	assert_int_equal(stack.x, 0);
	assert_int_equal(stack.y, 0);
	assert_int_equal(stack.width, 9);
	assert_int_equal(stack.height, 2);
}

void push_linear__col_zero(void **state) {
	struct Box usable = { .x = 1, .y = 2, .width = 5, .height = 11 };

	push_linear(NULL, 0, usable, false, 999);
}

void push_linear__col_one(void **state) {
	expect_river_push_view_dimensions(1, 2, 5, 11);

	struct Box usable = { .x = 1, .y = 2, .width = 5, .height = 11 };

	push_linear(NULL, 1, usable, false, 999);
}

void push_linear__col_many(void **state) {
	expect_river_push_view_dimensions(1, 2, 5, 4);
	expect_river_push_view_dimensions(1, 6, 5, 4);
	expect_river_push_view_dimensions(1, 10, 5, 3);

	struct Box usable = { .x = 1, .y = 2, .width = 5, .height = 11 };

	push_linear(NULL, 3, usable, false, 999);
}

void push_linear__col_empty(void **state) {
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);

	struct Box usable = { .x = 10, .y = 20, .width = 0, .height = 0 };

	push_linear(NULL, 3, usable, false, 999);
}

void push_linear__row_zero(void **state) {
	struct Box usable = { .x = 1, .y = 2, .width = 17, .height = 11 };

	push_linear(NULL, 0, usable, true, 999);
}

void push_linear__row_one(void **state) {
	expect_river_push_view_dimensions(1, 2, 17, 11);

	struct Box usable = { .x = 1, .y = 2, .width = 17, .height = 11 };

	push_linear(NULL, 1, usable, true, 999);
}

void push_linear__row_many(void **state) {
	expect_river_push_view_dimensions(1, 2, 6, 11);
	expect_river_push_view_dimensions(7, 2, 6, 11);
	expect_river_push_view_dimensions(13, 2, 5, 11);

	struct Box usable = { .x = 1, .y = 2, .width = 17, .height = 11 };

	push_linear(NULL, 3, usable, true, 999);
}

void push_linear__row_one_empty(void **state) {
	expect_river_push_view_dimensions(0, 0, 0, 0);

	struct Box usable = { .x = 0, .y = 0, .width = 0, .height = 0 };

	push_linear(NULL, 1, usable, true, 999);
}

void push_linear__row_empty(void **state) {
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);

	struct Box usable = { .x = 10, .y = 20, .width = 0, .height = 0 };

	push_linear(NULL, 3, usable, true, 999);
}

void push_dwindle__ne_many(void **state) {
	expect_river_push_view_dimensions(100, 100, 36, 37);
	expect_river_push_view_dimensions(136, 118, 35, 19);
	expect_river_push_view_dimensions(136, 100, 18, 18);
	expect_river_push_view_dimensions(154, 109, 17, 9);
	expect_river_push_view_dimensions(154, 100, 17, 9);

	struct Box usable = { .x = 100, .y = 100, .width = 71, .height = 37 };

	push_dwindle(NULL, 5, usable, NE, false, 999);
}

void push_dwindle__se_many(void **state) {
	expect_river_push_view_dimensions(100, 100, 37, 36);
	expect_river_push_view_dimensions(100, 136, 19, 35);
	expect_river_push_view_dimensions(119, 136, 18, 18);
	expect_river_push_view_dimensions(119, 154, 9, 17);
	expect_river_push_view_dimensions(128, 154, 9, 9);
	expect_river_push_view_dimensions(128, 163, 5, 8);
	expect_river_push_view_dimensions(133, 163, 4, 4);
	expect_river_push_view_dimensions(133, 167, 4, 4);

	struct Box usable = { .x = 100, .y = 100, .width = 37, .height = 71 };

	push_dwindle(NULL, 8, usable, SE, true, 999);
}

void push_dwindle__sw_many(void **state) {
	expect_river_push_view_dimensions(32, 0, 32, 32);
	expect_river_push_view_dimensions(0, 0, 32, 16);
	expect_river_push_view_dimensions(16, 16, 16, 16);
	expect_river_push_view_dimensions(0, 16, 16, 8);
	expect_river_push_view_dimensions(8, 24, 8, 8);
	expect_river_push_view_dimensions(0, 24, 8, 8);

	struct Box usable = { .x = 0, .y = 0, .width = 64, .height = 32 };

	push_dwindle(NULL, 6, usable, SW, false, 999);
}

void push_dwindle__nw_many(void **state) {
	expect_river_push_view_dimensions(100, 135, 37, 36);
	expect_river_push_view_dimensions(118, 100, 19, 35);
	expect_river_push_view_dimensions(100, 117, 18, 18);
	expect_river_push_view_dimensions(100, 100, 18, 17);

	struct Box usable = { .x = 100, .y = 100, .width = 37, .height = 71 };

	push_dwindle(NULL, 4, usable, NW, true, 999);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(push_monocle__zero),
		cmocka_unit_test(push_monocle__one),
		cmocka_unit_test(push_monocle__many),

		cmocka_unit_test(calc_master_stack__zero),

		cmocka_unit_test(calc_master_stack__left_one),
		cmocka_unit_test(calc_master_stack__left_many),

		cmocka_unit_test(calc_master_stack__right_one),
		cmocka_unit_test(calc_master_stack__right_many),

		cmocka_unit_test(calc_master_stack__top_one),
		cmocka_unit_test(calc_master_stack__top_many),

		cmocka_unit_test(calc_master_stack__bottom_one),
		cmocka_unit_test(calc_master_stack__bottom_many),

		cmocka_unit_test(push_linear__col_zero),
		cmocka_unit_test(push_linear__col_one),
		cmocka_unit_test(push_linear__col_many),
		cmocka_unit_test(push_linear__col_empty),

		cmocka_unit_test(push_linear__row_zero),
		cmocka_unit_test(push_linear__row_one),
		cmocka_unit_test(push_linear__row_many),
		cmocka_unit_test(push_linear__row_empty),

		cmocka_unit_test(push_dwindle__ne_many),
		cmocka_unit_test(push_dwindle__se_many),
		cmocka_unit_test(push_dwindle__sw_many),
		cmocka_unit_test(push_dwindle__nw_many),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

