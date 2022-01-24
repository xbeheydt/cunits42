#ifdef __linux__
# include <mcheck.h>
#endif

#include "memcheck.h"
#include "memcheck_internal.h"
#include "cunits42_internal.h"


/* Internal functions */
#ifdef __linux__
void    abortfn_enable(enum mcheck_status status)
{
	switch (status)
	{
	case MCHECK_DISABLED:
		print_ko("Memory check disable", NOENDL);
		break;
	case MCHECK_OK:
		print_ko("Memory check OK", NOENDL);
		break;
	case MCHECK_FREE:
		print_ok("Freeing", NOENDL);
		break;
	case MCHECK_HEAD:
		print_ko("Head memory leak detected", NOENDL);
		break;
	case MCHECK_TAIL:
		print_ko("Tail memory leak detected", NOENDL);
		break;
	default:
		break;
	}
}
#endif
