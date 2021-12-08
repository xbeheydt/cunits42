/* needed by dlfcn.h */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif

/* external libs includes */
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
// #include <execinfo.h> see bracktrace usage TODO
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <errno.h>
#include <malloc.h>
#include <time.h>
#include <dlfcn.h>

#include "memtrace.h"
#include "memtrace_internal.h"

/* proc paths */
//static const char	*g_statm_path			= TRACE_MEM_STATM_PATH;
//static const char	*g_maps_path			= TRACE_MEM_MAPS_PATH;

/* handler declarations */
static void	*(*real_malloc)(size_t size)	= NULL;
static void	 (*real_free)(void *prt)		= NULL;

/* DL resolving */
#define DL_RESOLVE(fcn) \
	((!real_ ## fcn) ? (real_ ## fcn = dlsym(RTLD_NEXT, # fcn)) : (real_ ## fcn = ((void *)0x1)))

/* data context */
static trace_mem_ctx_t	g_ctx				= TRACE_MEM_CTX_BASE;

/* intenal api functions */
trace_mem_ctx_t	*trace_mem_ctx_get(void)
{
	return (&g_ctx);
}

/* constructor/destructor inits/fini */
static void	__init_lib(void)
{
	/* get real functions ptrs */
	DL_RESOLVE(malloc);
	DL_RESOLVE(free);
	g_ctx.init_done = TRACE_MEM_INIT;
}

static void	__attribute__ ((constructor))trace_mem_init(void)
{
	__init_lib();
	return ;
}

static void	__fini_lib(void)
{
	g_ctx.init_done = TRACE_MEM_FINI;
	return ;
}

static void	__attribute__ ((destructor))trace_mem_fini(void)
{
	__fini_lib();
	return ;
}

/* log alloc handlers */
static lst_alloc_t	*lst_alloc_new(void *ptr, size_t size, const char *fname, uint8_t line, const char *fcn)
{
	lst_alloc_t	*new;

	if ((new = real_malloc(sizeof (lst_alloc_t))) != NULL)
	{
		new->ptr	= ptr;
		new->size	= size;
		new->fname	= fname;
		new->line	= line;
		new->fcn	= fcn;
		new->next	= NULL;
	}
	return (new);
}

static void	lst_alloc_push(lst_alloc_t **allocs, lst_alloc_t *new)
{
	if ((*allocs) != NULL)
		(*allocs)->next = new;
	else
		(*allocs) = new;
}

static lst_alloc_t	*lst_alloc_pop(lst_alloc_t **allocs, void *ptr)
{
	lst_alloc_t	*current;
	lst_alloc_t	*ret;

	current = NULL;
	if ((*allocs))
	{
		current = (*allocs);
		while (current)
		{
			if (current->ptr == ptr)
			{
				ret = current;
				current = current->next;
				return (ret);
			}
			current = current->next;
		}
	}
	return (current);
}

/* library functions */
void	*__malloc(size_t size, const char *fname, uint8_t line, const char *fcn)
{
	void	*ptr;

	// TODO : logging if ptr is not NULL
	if ((ptr = real_malloc(size)) != NULL)
	{
		lst_alloc_push(&(g_ctx.allocs), lst_alloc_new(ptr, size, fname, line, fcn));
		g_ctx.mem_used += size;
		g_ctx.stat.malloc++;
	}
	return (ptr);
}

void	__free(void *ptr, const char *fname, uint8_t line, const char *fcn)
{
	(void)fname; (void)line; (void)fcn; // TODO implement logging
	lst_alloc_t	*current;

	// TODO : logging is ptr is NULL
	current = lst_alloc_pop(&(g_ctx.allocs), ptr);
	real_free(ptr);
	g_ctx.mem_used -= current->size;
	g_ctx.stat.free++;
	real_free(current);
}
