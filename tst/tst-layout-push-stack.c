#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>	// IWYU pragma: keep

#include <cmocka.h>
#include "tst.h"	// IWYU pragma: keep

#include "config.h"
#include "tag.h"

#include "layout.h"

int setup(void **state) {
	config()->log_threshold = DEBUG;
	return 0;
}

int teardown(void **state) {
	return 0;
}

void push_stack__one(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	expect_river_push_view_dimensions(1, 2, 5, 11);

	push_stack(demand, EVEN, N, N, 1, 1, usable, usable);
}

void push_stack__n(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	expect_river_push_view_dimensions(1, 7, 5, 6);
	expect_river_push_view_dimensions(1, 2, 5, 5);

	push_stack(demand, EVEN, N, N, 2, 2, usable, usable);
}

void push_stack__s(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	expect_river_push_view_dimensions(1, 2, 5, 6);
	expect_river_push_view_dimensions(1, 8, 5, 5);

	push_stack(demand, EVEN, S, S, 2, 2, usable, usable);
}

void push_stack__e(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	expect_river_push_view_dimensions(1, 2, 3, 11);
	expect_river_push_view_dimensions(4, 2, 2, 11);

	push_stack(demand, EVEN, E, E, 2, 2, usable, usable);
}

void push_stack__w(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	expect_river_push_view_dimensions(3, 2, 3, 11);
	expect_river_push_view_dimensions(1, 2, 2, 11);

	push_stack(demand, EVEN, W, W, 2, 2, usable, usable);
}

void push_stack__even(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	expect_river_push_view_dimensions(1, 2, 5, 4);
	expect_river_push_view_dimensions(1, 6, 5, 4);
	expect_river_push_view_dimensions(1, 10, 5, 3);

	push_stack(demand, EVEN, S, S, 3, 3, usable, usable);
}

void push_stack__diminish(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 0, 0, 97, 1, };

	expect_river_push_view_dimensions(0,  0, 24, 1); // 7/28
	expect_river_push_view_dimensions(24, 0, 21, 1); // 6/28 up
	expect_river_push_view_dimensions(45, 0, 17, 1); // 5/28
	expect_river_push_view_dimensions(62, 0, 14, 1); // 4/28 up
	expect_river_push_view_dimensions(76, 0, 10, 1); // 3/28
	expect_river_push_view_dimensions(86, 0,  7, 1); // 2/28 up
	expect_river_push_view_dimensions(93, 0,  4, 1); // 1/28

	push_stack(demand, DIMINISH, E, E, 7, 7, usable, usable);
}

void push_stack__dwindle(void **state) {
	struct Demand demand = { 0 };
	struct Box usable = { 100, 100, 37, 71, };

	expect_river_push_view_dimensions(100, 100, 37, 36);
	expect_river_push_view_dimensions(100, 136, 19, 35);
	expect_river_push_view_dimensions(119, 136, 18, 18);
	expect_river_push_view_dimensions(119, 154, 9, 17);
	expect_river_push_view_dimensions(128, 154, 9, 9);
	expect_river_push_view_dimensions(128, 163, 5, 8);
	expect_river_push_view_dimensions(133, 163, 4, 4);
	expect_river_push_view_dimensions(133, 167, 4, 4);

	push_stack(demand, DWINDLE, S, E, 8, 8, usable, usable);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(push_stack__one),

		cmocka_unit_test(push_stack__n),
		cmocka_unit_test(push_stack__s),
		cmocka_unit_test(push_stack__e),
		cmocka_unit_test(push_stack__w),

		cmocka_unit_test(push_stack__even),

		cmocka_unit_test(push_stack__diminish),

		cmocka_unit_test(push_stack__dwindle),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

