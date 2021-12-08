#include <stdio.h>
#include "memtrace.h"
#include "memtrace_internal.h"

void	trace_mem_get_stat(void)
{
	trace_mem_ctx_t	*ctx;

	ctx = trace_mem_ctx_get();
	printf("malloc %u, free %u\n", ctx->stat.malloc, ctx->stat.free);
}

void	trace_mem_get_stat_detailed(void)
{

	trace_mem_ctx_t	*ctx;
	lst_alloc_t	*alloc;

	ctx = trace_mem_ctx_get();
	alloc = ctx->allocs;
	while (alloc)
	{
		printf("ptr %p, size %ld, file %s, line %u, fcn %s\n",
				alloc->ptr, alloc->size, alloc->fname, alloc->line, alloc->fcn);
		alloc = alloc->next;
	}
}
