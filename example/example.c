#include <cunits42.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static cunits42_t	test_strcmp(void)
{
	// Test OK
	UNIT_TEST(strcmp("Hello", "Hello"), ==, strcmp("Hello", "Hello"));

	// Test KO
	UNIT_TEST(strcmp("Hello", "Hello"), ==, strcmp("hello", "Hello"));
	return (CUNITS42_OK);
}

static cunits42_t	test_skipped(void)
{
	UNIT_TEST(1, !=, 2);
	return (CUNITS42_OK);
}

static cunits42_test_t	tests[] = {
	{ TEST_FCN(test_strcmp), NULL, NULL, CUNITS42_RUN },
	{ TEST_FCN(test_skipped), NULL, NULL, CUNITS42_SKIP },
	TEST_END
};

int	main(int argc, const char *argv[])
{
	return (main_test(tests, argc, argv));
}
