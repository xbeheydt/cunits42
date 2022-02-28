#include <cunits42.h>
#include "cunits42_internal.h"

#include <stdio.h>

/* Globals */
static	cunits42_cfg_t	g_cfg = CUNITS42_DEFAULT_CFG;

/* Internal API */
void	print_skip(const char *s, const char *endl)
{
	dprintf(g_cfg.logfd, "[%sSKIP%s] %s%s", FG_YELLOW, RESET_COLOR, s, endl);
}

void	print_ok(const char *s, const char *endl)
{
	dprintf(g_cfg.logfd, "[%sOK%s] %s%s", FG_GREEN, RESET_COLOR, s, endl);
}

void	print_ko(const char *s, const char *endl)
{
	dprintf(g_cfg.logfd, "[%sKO%s] %s%s", FG_RED, RESET_COLOR, s, endl);
}

/* Private functions */
static cunits42_t	run_test(cunits42_test_t test)
{
	cunits42_t	ret;

	ret = CUNITS42_OK;
	if (test.state == CUNITS42_RUN)
	{
		if (test.setupFcn)
			test.setupFcn();
		ret = test.testFcn();
		if (test.teardownFcn)
			test.teardownFcn();
		if (ret == (cunits42_t)CUNITS42_SKIP) // TODO : improve condition
		{
			print_skip("Test are skipped by condition.", SPACE);
			ret = CUNITS42_OK;
		}
	}
	else
		print_skip("Skipped test", SPACE);
	if (g_cfg.stop == CUNITS42_STOP && ret == CUNITS42_KO)
		exit(ret); // TODO : make a cleaning function with atexit
	return (ret);
}

/* Public API */
cunits42_t	main_test(cunits42_test_t *tests, int argc, const char *argv[])
{
	(void)argc; (void)argv; // TODO : implement argument parsing
	int	itest;
	cunits42_t	ret;

	itest	= 0;
	ret		= CUNITS42_OK;
	while (tests[itest].state != CUNITS42_STOP)
	{
		dprintf(g_cfg.logfd, "%s : ", tests[itest].testName);
		if (ret == CUNITS42_OK && (run_test(tests[itest])) == CUNITS42_KO)
			ret = CUNITS42_KO;
		++itest;
		printf("\n");
	}
	// TODO : print global result is only summary
	return (ret);
}

cunits42_t	unit_test(bool condition, const char *msg)
{
	if (condition)
		print_ok("", SPACE);
	else
		print_ko(msg, SPACE);
	return ((condition) ? CUNITS42_OK : CUNITS42_KO);
}

