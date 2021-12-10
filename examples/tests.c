#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cunits42.h"

static cunits42_t	test_strcmp(void)
{
	// Test OK
	UNIT_TEST(strcmp("Hello", "Hello"), ==, strcmp("Hello", "Hello"));

	// Test KO
	UNIT_TEST(strcmp("Hello", "Hello"), ==, strcmp("hello", "Hello"));
	return (CUNITS42_OK);
}

static cunits42_t	test_detailled(void)
{
	int	a;
	int	b;

	// test OK
	a = 1;
	b = 1;
	UNIT_TEST_DETAILED(a, ==, b, "a=%d == b=%d", a, b);

	// test KO
	a = 1;
	b = 2;
	UNIT_TEST_DETAILED(a, ==, b, "a=%d != b=%d", a, b);

	return (CUNITS42_OK);
}

static cunits42_test_t	tests[] = {
	{ TEST_FCN(test_strcmp), NULL, NULL, CUNITS42_RUN },
	{ TEST_FCN(test_detailled), NULL, NULL, CUNITS42_RUN },
	//. TODO : Skiped test
	CUNITS42_TEST_STOP
};

int	main(int argc, const char *argv[])
{
	return (main_test(tests, argc, argv));
}
