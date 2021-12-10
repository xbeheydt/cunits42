#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include "cunits42.h"
#include "cunits42_internal.h"

/* global configs */
static	cunits42_cfg_t	g_cfg = CUNITS42_DEFAULT_CFG;

/* internal functions */
static void	print_skip(const char *s, const char *endl)
{
	dprintf(g_cfg.logfd, "[%sSKIP%s] %s%s", FG_YELLOW, RESET_COLOR, s, endl);
}

static void	print_ok(const char *s, const char *endl)
{
	dprintf(g_cfg.logfd, "[%sOK%s] %s%s", FG_GREEN, RESET_COLOR, s, endl);
}

static void	print_ko(const char *s, const char *endl)
{
	dprintf(g_cfg.logfd, "[%sKO%s] %s%s", FG_RED, RESET_COLOR, s, endl);
}

static cunits42_t	run_test(cunits42_test_t test)
{
	cunits42_t	ret;

	ret = CUNITS42_OK;
	if (test.state == CUNITS42_RUN)
	{
		if (test.setup)
			test.setup();
		ret = test.fcn();
		if (test.teardown)
			test.teardown();
	}
	else
		print_skip(test.name, ENDL);
	if (g_cfg.stop == CUNITS42_STOP && ret == CUNITS42_KO)
		exit(ret); // TODO : make a cleaning function with atexit
	return (ret);
}

/* API functions */
cunits42_t	unit_test(bool condition, const char *fmt, ...)
{
	va_list	args;
	char	s[BUF_MSG];

	if (condition)
		print_ok("", NOENDL);
	else
	{
		va_start(args, fmt);
		vsprintf(s, fmt, args);
		print_ko(s, NOENDL);
		va_end(args);
	}
	return ((condition) ? CUNITS42_OK : CUNITS42_KO);
}

cunits42_t	main_test(cunits42_test_t *tests, int argc, const char *argv[])
{
	(void)argc; (void)argv; // TODO : implement argument parsing
	int	itest;
	cunits42_t	ret;

	itest	= 0;
	ret		= CUNITS42_OK;
	while (tests[itest].state != CUNITS42_STOP)
	{
		dprintf(g_cfg.logfd, "%s : ", tests[itest].name);
		if (ret == CUNITS42_OK && (run_test(tests[itest])) == CUNITS42_KO)
			ret = CUNITS42_KO;
		++itest;
		printf("\n");
	}
	// TODO : print global result is only summary
	return (ret);
}
