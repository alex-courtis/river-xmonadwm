#include <setjmp.h>	// IWYU pragma: keep
#include <stdarg.h>	// IWYU pragma: keep
#include <stddef.h>
#include <stdbool.h>

#include <cmocka.h>
#include "tst.h"

int setup(void **state) {
	return 0;
}

int teardown(void **state) {
	return 0;
}

void push_monocle__zero(void **state) {
	struct Demand demand = { .view_count = 0, .usable_width = 9, .usable_height = 5, };

	push_monocle(demand);
}

void push_monocle__one(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);

	struct Demand demand = { .view_count = 1, .usable_width = 9, .usable_height = 5, };

	push_monocle(demand);
}

void push_monocle__many(void **state) {
	expect_river_push_view_dimensions(0, 0, 9, 5);
	expect_river_push_view_dimensions(0, 0, 9, 5);
	expect_river_push_view_dimensions(0, 0, 9, 5);

	struct Demand demand = { .view_count = 3, .usable_width = 9, .usable_height = 5, };

	push_monocle(demand);
}

void push_linear__col_zero(void **state) {
	struct Box usable = { 1, 2, 5, 11, };

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };

	push_linear(demand, tag, 0, usable, false);
}

void push_linear__col_one(void **state) {
	expect_river_push_view_dimensions(1, 2, 5, 11);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 1, 2, 5, 11, };

	push_linear(demand, tag, 1, usable, false);
}

void push_linear__col_many(void **state) {
	expect_river_push_view_dimensions(1, 2, 5, 4);
	expect_river_push_view_dimensions(1, 6, 5, 4);
	expect_river_push_view_dimensions(1, 10, 5, 3);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 1, 2, 5, 11, };

	push_linear(demand, tag, 3, usable, false);
}

void push_linear__col_empty(void **state) {
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 10, 20, 0, 0, };

	push_linear(demand, tag, 3, usable, false);
}

void push_linear__row_zero(void **state) {
	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 1, 2, 17, 11, };

	push_linear(demand, tag, 0, usable, true);
}

void push_linear__row_one(void **state) {
	expect_river_push_view_dimensions(1, 2, 17, 11);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 1, 2, 17, 11, };

	push_linear(demand, tag, 1, usable, true);
}

void push_linear__row_many(void **state) {
	expect_river_push_view_dimensions(1, 2, 6, 11);
	expect_river_push_view_dimensions(7, 2, 6, 11);
	expect_river_push_view_dimensions(13, 2, 5, 11);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 1, 2, 17, 11, };

	push_linear(demand, tag, 3, usable, true);
}

void push_linear__row_one_empty(void **state) {
	expect_river_push_view_dimensions(0, 0, 0, 0);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 0, 0, 0, 0, };

	push_linear(demand, tag, 1, usable, true);
}

void push_linear__row_empty(void **state) {
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);
	expect_river_push_view_dimensions(10, 20, 0, 0);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 10, 20, 0, 0, };

	push_linear(demand, tag, 3, usable, false);
}

void push_linear__exceeded_size(void **state) {
	expect_river_push_view_dimensions(10, 20, 3, 1);
	expect_river_push_view_dimensions(10, 21, 3, 1);
	expect_river_push_view_dimensions(10, 22, 3, 1);
	expect_river_push_view_dimensions(10, 23, 3, 0);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 10, 20, 3, 3, };

	push_linear(demand, tag, 4, usable, false);
}

void push_dwindle__ne_many(void **state) {
	expect_river_push_view_dimensions(100, 100, 36, 37);
	expect_river_push_view_dimensions(136, 118, 35, 19);
	expect_river_push_view_dimensions(136, 100, 18, 18);
	expect_river_push_view_dimensions(154, 109, 17, 9);
	expect_river_push_view_dimensions(154, 100, 17, 9);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 100, 100, 71, 37, };

	push_dwindle(demand, tag, 5, usable, NE, false);
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

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 100, 100, 37, 71, };

	push_dwindle(demand, tag, 8, usable, SE, true);
}

void push_dwindle__sw_many(void **state) {
	expect_river_push_view_dimensions(32, 0, 32, 32);
	expect_river_push_view_dimensions(0, 0, 32, 16);
	expect_river_push_view_dimensions(16, 16, 16, 16);
	expect_river_push_view_dimensions(0, 16, 16, 8);
	expect_river_push_view_dimensions(8, 24, 8, 8);
	expect_river_push_view_dimensions(0, 24, 8, 8);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 0, 0, 64, 32, };

	push_dwindle(demand, tag, 6, usable, SW, false);
}

void push_dwindle__nw_many(void **state) {
	expect_river_push_view_dimensions(100, 135, 37, 36);
	expect_river_push_view_dimensions(118, 100, 19, 35);
	expect_river_push_view_dimensions(100, 117, 18, 18);
	expect_river_push_view_dimensions(100, 100, 18, 17);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.5, };
	struct Box usable = { 100, 100, 37, 71, };

	push_dwindle(demand, tag, 4, usable, NW, true);
}

void push_dwindle__se_many_larger(void **state) {
	expect_river_push_view_dimensions(0, 0, 72, 80);
	expect_river_push_view_dimensions(72, 0, 48, 48);
	expect_river_push_view_dimensions(72, 48, 29, 32);
	expect_river_push_view_dimensions(101, 48, 19, 19);
	expect_river_push_view_dimensions(101, 67, 19, 13);

	struct Demand demand = { 0 };
	struct Tag tag = { .ratio_stack = 0.6, };
	struct Box usable = { 0, 0, 120, 80, };

	push_dwindle(demand, tag, 5, usable, SE, false);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(push_monocle__zero),
		cmocka_unit_test(push_monocle__one),
		cmocka_unit_test(push_monocle__many),

		cmocka_unit_test(push_linear__col_zero),
		cmocka_unit_test(push_linear__col_one),
		cmocka_unit_test(push_linear__col_many),
		cmocka_unit_test(push_linear__col_empty),

		cmocka_unit_test(push_linear__row_zero),
		cmocka_unit_test(push_linear__row_one),
		cmocka_unit_test(push_linear__row_many),
		cmocka_unit_test(push_linear__row_empty),

		cmocka_unit_test(push_linear__exceeded_size),

		cmocka_unit_test(push_dwindle__ne_many),
		cmocka_unit_test(push_dwindle__se_many),
		cmocka_unit_test(push_dwindle__sw_many),
		cmocka_unit_test(push_dwindle__nw_many),

		cmocka_unit_test(push_dwindle__se_many_larger),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

