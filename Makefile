INCDIR			= ${CURDIR}/include
SRCDIR			= ${CURDIR}/src
LIBDIR			= ${CURDIR}/libs
BUILDDIR		= ${CURDIR}/build
EXAMPLESDIR		= ${CURDIR}/examples

STATIC			= ${LIBDIR}/libcunits42.a
SRCS			= ${SRCDIR}/cunits42.c
OBJS			= $(subst ${SRCDIR}, ${BUILDDIR}, ${SRCS:.c=.o})

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -g3
IFLAGS			= -I${INCDIR} -I${SRCDIR}

RM				= rm -rf

all: ${STATIC}

$(LIBDIR):
	mkdir ${LIBDIR}

$(BUILDDIR):
	mkdir ${BUILDDIR}

$(OBJS): $(BUILDDIR)
	$(CC) ${CFLAGS} ${IFLAGS} -c ${SRCS} -o ${OBJS}

$(STATIC): $(OBJS) $(LIBDIR)
	ar rcs ${STATIC} ${OBJS}
	ranlib ${STATIC}

libcunits.a: $(STATIC)

clean:
	$(RM) ${BUILDDIR}

fclean: clean
	$(RM) ${LIBDIR}
	$(RM) a.out

re: fclean all

examples: $(STATIC)
	@$(CC) ${CFLAGS} -I${INCDIR} -L${LIBDIR} ${EXAMPLESDIR}/tests.c -o a.out -lcunits42

run-examples: examples
	@./a.out

.PHONY: clean fclean examples re run-examples
