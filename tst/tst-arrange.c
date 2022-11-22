#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>	// IWYU pragma: keep

#include <cmocka.h>
#include "tst.h"	// IWYU pragma: keep

#include "list.h"

#include "arrange.h"

int setup(void **state) {
	return 0;
}

int teardown(void **state) {
	return 0;
}

void arrange_monocle__many(void **state) {
	struct SList *stack = NULL;
	struct Demand demand = { .view_count = 2, .usable_width = 5, .usable_height = 3 };

	arrange_monocle(demand, &stack);

	assert_int_equal(slist_length(stack), 2);

	assert_box_equal(slist_val(stack, 0), 0, 0, 5, 3);
	assert_box_equal(slist_val(stack, 1), 0, 0, 5, 3);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(arrange_monocle__many),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

