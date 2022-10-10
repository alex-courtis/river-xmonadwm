#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <inc2.h>

int setup(void **state) {
	return 0;
}

int teardown(void **state) {
	return 0;
}

int __wrap_add(int a, int b) {
	check_expected(a);
	check_expected(b);

	return mock();
}

void add_and_double__success(void **state) {
	expect_value(__wrap_add, a, 1);
	expect_value(__wrap_add, b, 2);
	will_return(__wrap_add, 7);

	assert_int_equal(add_and_double(1, 2), 14);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(add_and_double__success),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

