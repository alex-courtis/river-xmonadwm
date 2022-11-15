#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>	// IWYU pragma: keep

#include <cmocka.h>
#include "tst.h"	// IWYU pragma: keep

#include "config.h"
#include "tag.h"

#include "layout.h"

int setup(void **state) {
	return 0;
}

int teardown(void **state) {
	return 0;
}

void calc_master_stack__zero(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 0, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = LEFT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__one_count_two(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 1, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 2, .layout_cur = LEFT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 9, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__two_count_two(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 2, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 2, .layout_cur = LEFT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 9, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__three_count_two(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 3, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 2, .layout_cur = LEFT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 5, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 5, .y = 0, .width = 4, .height = 5, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__one_left(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 1, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = LEFT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 9, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__many_left(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 7, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = LEFT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 5, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 5, .y = 0, .width = 4, .height = 5, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__one_right(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 1, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = LEFT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 9, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__many_right(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 2, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = RIGHT, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 4, .y = 0, .width = 5, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 4, .height = 5, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__one_top(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 1, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = TOP, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 9, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__many_top(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 2, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = TOP, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 9, .height = 3, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 3, .width = 9, .height = 2, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__one_bottom(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 1, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = BOTTOM, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 0, .width = 9, .height = 5, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 0, .height = 0, };
	assert_box_equal(&stack, &stack_expected);
}

void calc_master_stack__many_bottom(void **state) {
	struct Box master, stack;

	struct Demand demand = { .view_count = 2, .usable_width = 9, .usable_height = 5, };
	struct Tag tag = { .count_master = 1, .layout_cur = BOTTOM, };

	calc_master_stack(demand, &tag, &master, &stack);

	struct Box master_expected = { .x = 0, .y = 3, .width = 9, .height = 3, };
	assert_box_equal(&master, &master_expected);

	struct Box stack_expected = { .x = 0, .y = 0, .width = 9, .height = 2, };
	assert_box_equal(&stack, &stack_expected);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(calc_master_stack__zero),

		cmocka_unit_test(calc_master_stack__one_count_two),
		cmocka_unit_test(calc_master_stack__two_count_two),
		cmocka_unit_test(calc_master_stack__three_count_two),

		cmocka_unit_test(calc_master_stack__one_left),
		cmocka_unit_test(calc_master_stack__many_left),

		cmocka_unit_test(calc_master_stack__one_right),
		cmocka_unit_test(calc_master_stack__many_right),

		cmocka_unit_test(calc_master_stack__one_top),
		cmocka_unit_test(calc_master_stack__many_top),

		cmocka_unit_test(calc_master_stack__one_bottom),
		cmocka_unit_test(calc_master_stack__many_bottom),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

