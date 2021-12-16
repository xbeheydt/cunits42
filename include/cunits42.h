#ifndef CUNITS42_H
# define CUNITS42_H

# include <stdbool.h>
# include <stdio.h>

/* constantes values */
typedef enum cunits42_e
{
	CUNITS42_OK,
	CUNITS42_KO,
}	cunits42_t;

typedef enum cunits_state_e
{
	CUNITS42_RUN,
	CUNITS42_SKIP,
	CUNITS42_CONTINUE,
	CUNITS42_STOP,
	CUNITS42_ENABLE,
	CUNITS42_DISABLE
}	cunits42_state_t;

typedef struct cunits42_test_s
{
	cunits42_t			(*fcn)(void);
	const char			*name;
	void				(*setup)(void);
	void				(*teardown)(void);
	cunits42_state_t	state;
}	cunits42_test_t;

# define TEST_FCN(fcn)	fcn, #fcn
# define CUNITS42_TEST_STOP	\
	{ NULL, NULL, NULL, NULL, CUNITS42_STOP }

/* API functions */
cunits42_t	main_test(cunits42_test_t *tests, int argc, const char *argv[]);

/* Utils functions */
int			redirect_stdout(cunits42_state_t state);

/* API tests */
cunits42_t	unit_test(bool condition, const char *fmt, ...);
# define	UNIT_TEST(a, op, b, ...) \
	unit_test(a op b, __VA_ARGS__);

cunits42_t	stdout_cmp(const char *s);
# define	STDOUT_TEST(fcn, s) \
	redirect_stdout(CUNITS42_ENABLE); \
	fcn; \
	redirect_stdout(CUNITS42_DISABLE); \
	stdout_cmp(s);

#endif /* CUNITS42_H */
