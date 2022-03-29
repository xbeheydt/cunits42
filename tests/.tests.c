/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbeheydt <xbeheydt@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:02:01 by xbeheydt          #+#    #+#             */
/*   Updated: 2022/03/09 11:02:01 by xbeheydt         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include ".tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static int	verbose_g = 0;

void	print_skip(const char *s, const char *endl)
{
	dprintf(1, "[%sSKIP%s] \"%s\"%s", FG_YELLOW, RESET_COLOR, s, endl);
}

void	print_ok(const char *s, const char *endl)
{
	if (verbose_g)
		dprintf(1, "[%sOK%s] \"%s\"%s", FG_GREEN, RESET_COLOR, s, endl);
	else
		dprintf(1, "[%sOK%s]%s", FG_GREEN, RESET_COLOR, endl);
}

void	print_ko(const char *s, const char *endl)
{
	if (verbose_g)
		dprintf(1, "[%sKO%s] \"%s\"%s", FG_RED, RESET_COLOR, s, endl);
	else
		dprintf(1, "[%sKO%s]%s", FG_RED, RESET_COLOR, endl);
}

/* Argument handlers */

static int	__test_activate(const char *name, args_t *args)
{
	int	i;

	i = 0;
	if (args->tests == NULL)
		return (1);
	while (args->tests[i])
	{
		if (strcmp(name, args->tests[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

static void	__clear_args(args_t **args)
{
	int	i;

	i = 0;
	if ((*args)->tests)
	{
		while ((*args)->tests[i])
		{
			free((*args)->tests[i]);
			++i;
		}
		free((*args)->tests);
	}
	free((*args));
}

static args_t	*__init_args(void)
{
	args_t *args;
	
	args = NULL;
	args = malloc(sizeof(args_t));
	if (args)
		args->tests = NULL;
	return (args);
}

static args_t	*__parse_args(int argc, const char *argv[])
{
	int	i;
	args_t	*args;

	i = 1;
	args = __init_args();
	while (argc > 1 && argv[i] != NULL)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'v')
			verbose_g = 1;
		else if (argv[i][0] == '-' && argv[i][1] == 't')
		{
			++i;
			args->tests = ft_split(argv[i], ',');
			if (args->tests == NULL)
			{
				__clear_args(&args);
				dprintf(1, "unit test - Error missing options for '-t'.\n");
				exit(1);
			}
		}
		else
		{
			__clear_args(&args);
			dprintf(1, "unit test - Error unknown arg '%s'.\n", argv[i]);
			exit(1);
		}
		++i;
	}
	return (args);
}

/* Main API */

static int __run_test(unit_t test, args_t *args)
{
	int	ret;
	int	activate;

	ret = OK;
	activate = __test_activate(test.name, args);
	if (activate && test.state == RUN)
	{
		dprintf(1, "%s : ", test.name);
		if (test.setupFcn)
			test.setupFcn(NULL);
		if (test.testFcn(NULL) == KO && ret == OK)
			ret = KO;
		if (test.teardownFcn)
			test.teardownFcn(NULL);
		dprintf(1, "\n");
	}
	if (activate && test.state == SKIP)
		print_skip("", ENDL);
	return (ret);
}

int	__main(int argc, const char *argv[], unit_t *tests)
{
	int	nb_test;
	int	ret;
	args_t	*args;

	nb_test = 0;
	ret = OK;
	args = __parse_args(argc, argv);
	while (tests[nb_test].state != END)
	{
		if (__run_test(tests[nb_test], args) == KO && ret == OK)
			ret = KO;
		++nb_test;
	}
	__clear_args(&args);
	return (ret);
}

/* test functions and macros */

int	unit_test(int condition, const char *msg)
{
	if (condition)
		print_ok(msg, SPACE);
	else
		print_ko(msg, SPACE);
	return ((condition) ? OK : KO);
}

char	*catch_fd(int redirect, int fd)
{
	static int	fddup;
	static int	p[2];
	char		buf[1024];
	char		*ret = NULL;
	ssize_t		s;
	size_t		sr = 0;
	if (redirect)
	{
		setbuf(stdout, NULL);
		pipe(p);
		fddup = dup(fd);
		dup2(p[1], fd);
		fcntl(p[0], F_SETFL, O_NONBLOCK);
	}
	else
	{
		while ((s = read(p[0], buf, 1024)) > 0)
		{
			ret = realloc(ret, (sr + s + 1) * sizeof(char));
			memcpy(ret + sr, buf, s);
			sr += s;
			ret[sr] = 0;
			if (s < 1024)
				break ;
		}
		close(p[0]);
		close(p[1]);
		dup2(fddup, fd);
		return (ret);
	}
	return (NULL);
}
