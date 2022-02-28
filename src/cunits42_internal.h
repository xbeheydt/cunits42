#ifndef CUNITS42_INTERNAL_H
# define CUNITS42_INTERNAL_H

# include <unistd.h>

/* Commons macros */
# define SPACE			" "
# define ENDL			"\n"

/* Colors */
# define RESET_COLOR	"\033[0m"

# define FG_BLACK		"\033[30m"
# define FG_RED			"\033[31m"
# define FG_GREEN		"\033[32m"
# define FG_YELLOW		"\033[33m"
# define FG_BLUE		"\033[34m"
# define FG_MAGENTA		"\033[35m"
# define FG_CYAN		"\033[36m"
# define FG_WHITE		"\033[37m"

# define BG_BLACK		"\033[40m"
# define BG_RED			"\033[41m"
# define BG_GREEN		"\033[42m"
# define BG_YELLOW		"\033[43m"
# define BG_BLUE		"\033[44m"
# define BG_MAGENTA		"\033[45m"
# define BG_CYAN		"\033[46m"
# define BG_WHITE		"\033[47m"

/* MACRO tools */
# define VARSTR(var)	#var

/* Test configs */
typedef struct cunits42_cfg_s
{
	cunits42_t			*(*testFcns)(void);
	cunits42_state_t	state;
	int					logfd;
	cunits42_state_t	stop;
}	cunits42_cfg_t;
# define CUNITS42_DEFAULT_CFG	\
	{							\
		NULL,					\
		CUNITS42_RUN,			\
		STDOUT_FILENO,			\
		CUNITS42_CONTINUE		\
	}

/* GUI - print functions */
void	print_skip(const char *s, const char *endl);
void	print_ok(const char *s, const char *endl);
void	print_ko(const char *s, const char *endl);

#endif /* CUNITS42_INTERNAL_H */
