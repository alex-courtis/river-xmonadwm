#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <setjmp.h>
#include <cmocka.h>

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

void apply_view_dimensions__left_one(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);

	push_view_dimensions(LAYOUT_LEFT, NULL, 1, 9, 5, 999);
}

void apply_view_dimensions__left_two(void **state) {
	expect_river_push_view_dimensions(0, 0, 5, 5);
	expect_river_push_view_dimensions(5, 0, 4, 5);

	push_view_dimensions(LAYOUT_LEFT, NULL, 2, 9, 5, 999);
}

void apply_view_dimensions__left_three(void **state) {
	expect_river_push_view_dimensions(0, 0, 5, 5);
	expect_river_push_view_dimensions(5, 0, 4, 3);
	expect_river_push_view_dimensions(5, 3, 4, 2);

	push_view_dimensions(LAYOUT_LEFT, NULL, 3, 9, 5, 999);
}

void apply_view_dimensions__right_one(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);

	push_view_dimensions(LAYOUT_RIGHT, NULL, 1, 9, 5, 999);
}

void apply_view_dimensions__right_two(void **state) {
	expect_river_push_view_dimensions(4, 0, 5, 5);
	expect_river_push_view_dimensions(0, 0, 4, 5);

	push_view_dimensions(LAYOUT_RIGHT, NULL, 2, 9, 5, 999);
}

void apply_view_dimensions__right_three(void **state) {
	expect_river_push_view_dimensions(4, 0, 5, 5);
	expect_river_push_view_dimensions(0, 0, 4, 3);
	expect_river_push_view_dimensions(0, 3, 4, 2);

	push_view_dimensions(LAYOUT_RIGHT, NULL, 3, 9, 5, 999);
}

void apply_layout_monocle__one(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);

	push_view_dimensions(LAYOUT_MONOCLE, NULL, 1, 9, 5, 999);
}

void apply_layout_monocle__three(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);
	expect_river_push_view_dimensions(0, 0, 9, 5);
	expect_river_push_view_dimensions(0, 0, 9, 5);

	push_view_dimensions(LAYOUT_MONOCLE, NULL, 3, 9, 5, 999);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(apply_view_dimensions__left_one),
		cmocka_unit_test(apply_view_dimensions__left_two),
		cmocka_unit_test(apply_view_dimensions__left_three),
		cmocka_unit_test(apply_view_dimensions__right_one),
		cmocka_unit_test(apply_view_dimensions__right_two),
		cmocka_unit_test(apply_view_dimensions__right_three),
		cmocka_unit_test(apply_layout_monocle__one),
		cmocka_unit_test(apply_layout_monocle__three),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

