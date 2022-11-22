#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>	// IWYU pragma: keep

#include <cmocka.h>
#include "tst.h"	// IWYU pragma: keep

#include "config.h"
#include "list.h"

#include "layout.h"

int setup(void **state) {
	return 0;
}

int teardown(void **state) {
	return 0;
}

void layout_views__one(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	layout_views(demand, EVEN, N, N, 1, 1, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 1);

	assert_boxes_equal(stack->val, &usable);
}

void layout_views__n(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	layout_views(demand, EVEN, N, N, 2, 2, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 2);

	assert_box_equal(slist_val(stack, 0), 1, 7, 5, 6);
	assert_box_equal(slist_val(stack, 1), 1, 2, 5, 5);
}

void layout_views__s(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	layout_views(demand, EVEN, S, S, 2, 2, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 2);

	assert_box_equal(slist_val(stack, 0), 1, 2, 5, 6);
	assert_box_equal(slist_val(stack, 1), 1, 8, 5, 5);
}

void layout_views__e(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	layout_views(demand, EVEN, E, E, 2, 2, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 2);

	assert_box_equal(slist_val(stack, 0), 1, 2, 3, 11);
	assert_box_equal(slist_val(stack, 1), 4, 2, 2, 11);
}

void layout_views__w(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	layout_views(demand, EVEN, W, W, 2, 2, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 2);

	assert_box_equal(slist_val(stack, 0), 3, 2, 3, 11);
	assert_box_equal(slist_val(stack, 1), 1, 2, 2, 11);
}

void layout_views__even(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 1, 2, 5, 11, };

	layout_views(demand, EVEN, S, S, 3, 3, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 3);

	assert_box_equal(slist_val(stack, 0), 1, 2, 5, 4);
	assert_box_equal(slist_val(stack, 1), 1, 6, 5, 4);
	assert_box_equal(slist_val(stack, 2), 1, 10, 5, 3);
}

void layout_views__diminish(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 0, 0, 97, 1, };

	layout_views(demand, DIMINISH, E, E, 7, 7, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 7);

	assert_box_equal(slist_val(stack, 0), 0,  0, 24, 1); // 7/28
	assert_box_equal(slist_val(stack, 1), 24, 0, 21, 1); // 6/28 up
	assert_box_equal(slist_val(stack, 2), 45, 0, 17, 1); // 5/28
	assert_box_equal(slist_val(stack, 3), 62, 0, 14, 1); // 4/28 up
	assert_box_equal(slist_val(stack, 4), 76, 0, 10, 1); // 3/28
	assert_box_equal(slist_val(stack, 5), 86, 0,  7, 1); // 2/28 up
	assert_box_equal(slist_val(stack, 6), 93, 0,  4, 1); // 1/28
}

void layout_views__dwindle(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { 0 };
	struct Box usable = { 100, 100, 37, 71, };

	layout_views(demand, DWINDLE, S, E, 8, 8, usable, usable, &stack);

	assert_int_equal(slist_length(stack), 8);

	assert_box_equal(slist_val(stack, 0), 100, 100, 37, 36);
	assert_box_equal(slist_val(stack, 1), 100, 136, 19, 35);
	assert_box_equal(slist_val(stack, 2), 119, 136, 18, 18);
	assert_box_equal(slist_val(stack, 3), 119, 154, 9, 17);
	assert_box_equal(slist_val(stack, 4), 128, 154, 9, 9);
	assert_box_equal(slist_val(stack, 5), 128, 163, 5, 8);
	assert_box_equal(slist_val(stack, 6), 133, 163, 4, 4);
	assert_box_equal(slist_val(stack, 7), 133, 167, 4, 4);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(layout_views__one),

		cmocka_unit_test(layout_views__n),
		cmocka_unit_test(layout_views__s),
		cmocka_unit_test(layout_views__e),
		cmocka_unit_test(layout_views__w),

		cmocka_unit_test(layout_views__even),

		cmocka_unit_test(layout_views__diminish),

		cmocka_unit_test(layout_views__dwindle),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

