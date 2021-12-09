INCDIR			= ${CURDIR}/include
SRCDIR			= ${CURDIR}/src
LIBDIR			= ${CURDIR}/libs
BUILDDIR		= ${CURDIR}/build
EXAMPLESDIR		= ${CURDIR}/examples

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -g3
RM				= rm -rf
IFLAGS			= -I${INCDIR} -I${SRCDIR}

LIBCUNITS42			= libcunits42.a
LIBCUNITS42_SRCS	= ${SRCDIR}/cunits42.c
LIBCUNITS42_OBJS	= $(subst ${SRCDIR}, ${BUILDDIR}, ${LIBCUNITS42_SRCS:.c=.o})

$(LIBDIR):
	mkdir ${LIBDIR}

$(BUILDDIR):
	mkdir ${BUILDDIR}

$(LIBCUNITS42_OBJS): $(BUILDDIR)
	$(CC) ${CFLAGS} ${IFLAGS} -c ${LIBCUNITS42_SRCS} -o ${LIBCUNITS42_OBJS}

$(LIBCUNITS42): $(LIBCUNITS42_OBJS) $(LIBDIR)
	ar rcs ${LIBDIR}/${LIBCUNITS42} ${LIBCUNITS42_OBJS}
	ranlib ${LIBDIR}/${LIBCUNITS42}

clean:
	$(RM) ${BUILDDIR}

fclean: clean
	$(RM) ${LIBDIR}

examples: $(LIBCUNITS42)
	$(CC) ${CFLAGS} ${IFLAGS} ${EXAMPLESDIR}/tests.c -L${LIBDIR} -lcunits42 -o ${BUILDDIR}/examples
	exec ${BUILDDIR}/examples

.PHONY: clean fclean examples
