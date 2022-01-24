#ifndef MEMCHECK_INTERNAL_H
# define MEMCHECK_INTERNAL_H

# ifdef __linux__
#  include <mcheck.h>
# endif

/* MCHECK - helpers detects Heap Consistency Checking */
# ifdef __linux__
void    abortfn_enable(enum mcheck_status status);
# endif

#endif /* MEMCHECK_INTERNAL_H */
