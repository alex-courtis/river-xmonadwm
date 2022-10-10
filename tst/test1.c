#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <inc1.h>

int setup(void **state) {
	return 0;
}

int teardown(void **state) {
	return 0;
}

void add__success(void **state) {
	assert_int_equal(add(1, 2), 3);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(add__success),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

