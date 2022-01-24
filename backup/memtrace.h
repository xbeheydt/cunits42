#ifndef MEMTRACE_H
# define MEMTRACE_H

# include <stdio.h>
# include <stdint.h>
# include <assert.h>

# ifndef MEMTRACE_STATM_PATH
#  define MEMTRACE_STATM_PATH	"/proc/self/statm"
/**
 * /proc/[pid]/statm
 *
 * Provides information about memory usage, measured in
 * pages. The columns are :
 *
 * (1) (2) (3) (4) (5) (6) (7)
 *
 *		- (1) : size		total size program
 *		- (2) : resident	resident set size
 *		- (3) : shared		number of resident shared pages
 *		- (4) : text		text (code)
 *		- (5) : lib			library
 *		- (6) : data		data + stack
 *		- (7) : dt			dirty pages
 *
 * Proc man page is `man 5 proc`.
 */
# endif

# ifndef MEMTRACE_MAPS_PATH
#  define MEMTRACE_MAPS_PATH	"/proc/self/maps"
/**
 * /proc/[pid]/maps
 *
 * A file containing the currently mapped memory regions and
 * their access permissions.
 *
 * The `address` field is the adresse space in the process that
 * the mapping occupies.
 *
 * The `perms` field is a set of permission :
 *
 *	r = read
 *	w = write
 *	s = shared
 *	p = private (copy on write)
 *
 * The `offset` field is the offset into the file/whatever; dev
 * is the device (major:minor); inode is the inode on that
 * device. 0 indicates that no inode is associated with the
 * memory region, as would be the case with BSS
 * (uninitialized data).))
 *
 * The `pathname` field will usually be the file that is
 * backing the mapping.  For ELF files, you can easily
 * coordinate with the offset field by looking at the Offset
 * field in the ELF program headers (readelf -l).)
 *
 * There are additional helpful pseudo-paths :
 *
 *	[stack]
 *		The initial process's (also know as the main thrad's)
 *		stack.
 *
 *	[vdso]
 *		The virtual dynamically linked shared object. See vdso(7).
 *
 *	[heap]
 *		The process's heap
 *
 * For further informations see proc(5).
 */
# endif

/* overriding mem allocation */
void	*__malloc(size_t size, const char *fname, uint8_t line, const char *fcn);
# define malloc(size)	\
	__malloc(size, __FILE__, __LINE__, __func__);

void	__free(void *ptr, const char *fname, uint8_t line, const char *fcn);
# define free(ptr)	\
	__free(ptr, __FILE__, __LINE__, __func__);

/* api functions */
void	trace_mem_get_stat(void);
void	trace_mem_get_stat_detailed(void);

#endif /* MEMTRACE_H */
