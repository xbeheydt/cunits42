#ifndef CUNITS42_H
# define CUNITS42_H

# include <stdlib.h>
# include <stdbool.h>

/* Return types */
typedef enum cunits42_e
{
	CUNITS42_KO,
	CUNITS42_OK,
}	cunits42_t;

/* State functions */
typedef enum cunits42_state_e
{
	CUNITS42_RUN,
	CUNITS42_STOP,
	CUNITS42_CONTINUE,
	CUNITS42_SKIP,
	CUNITS42_ENABLE,
	CUNITS42_DISABLE,
}	cunits42_state_t;

/* Struct to config a test */
typedef struct cunits42_test_s
{
	const char		*testName;
	cunits42_t		(*testFcn)(void);
	void			(*setupFcn)(void);
	void			(*teardownFcn)(void);
	cunits42_state_t	state;
}	cunits42_test_t;

# define TEST_FCN(fcn)	#fcn, fcn
# define TEST_END \
	{ NULL, NULL, NULL, NULL, CUNITS42_STOP}

/* API */
cunits42_t	main_test(cunits42_test_t *tests, int argc, const char *argv[]);

/* Tests API */
cunits42_t	unit_test(bool condition, const char *msg);
# define	UNIT_TEST(a, op, b) \
	unit_test(a op b, "'"#a" "#op" "#b"'");


#endif /* CUNITS42_H */