#include <setjmp.h>  // IWYU pragma: keep
#include <stdarg.h>  // IWYU pragma: keep
#include <stddef.h>  // IWYU pragma: keep

#include <cmocka.h>

#include "tag.h"

int setup(void **state) {
	*state = tags_init();
	assert_non_null(*state);
	return 0;
}

int teardown(void **state) {
	tags_destroy(*state);
	return 0;
}

// no mask match
void tag_first__none(void **state) {
	const struct Tag *tag = tag_first(*state, 0x0);
	assert_non_null(tag);
	assert_int_equal(tag->mask, 0x1);
}

// exact mask match
void tag_first__equal(void **state) {
	const struct Tag *tag = tag_first(*state, 0x2);
	assert_non_null(tag);
	assert_int_equal(tag->mask, 0x2);
}

// first mask match
void tag_first__first(void **state) {
	const struct Tag *tag = tag_first(*state, 0x4 | 0x8);
	assert_non_null(tag);
	assert_int_equal(tag->mask, 0x4);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(tag_first__none),
		cmocka_unit_test(tag_first__equal),
		cmocka_unit_test(tag_first__first),
	};

	return cmocka_run_group_tests(tests, setup, teardown);
}

