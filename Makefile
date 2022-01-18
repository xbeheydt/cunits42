SRCDIR		= ${CURDIR}/src
BUILDDIR	= ${CURDIR}/build
LIBDIR		= ${CURDIR}/lib
EXAMPLESDIR	= ${CURDIR}/examples

TARGET		= ${LIBDIR}/libcunits42.a

SRCS		= ${SRCDIR}/cunits42.c \
			  ${SRCDIR}/memcheck.c \
			  ${SRCDIR}/memcheck_api.c
OBJS		= $(subst ${SRCDIR},${BUILDDIR}, ${SRCS:.c=.o})

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g3
IFLAGS		= -Iinclude -Isrc

ifeq ($(OS),Windos_NT)
	RM		= rm -Force
	MKDIR	= mkdir
	SEP		= \\
else
	RM		= rm -rf
	MKDIR	= mkdir -p
	SEP		= /
endif

all: directories ${TARGET}

directories:
	$(MKDIR) ${BUILDDIR}
	$(MKDIR) ${LIBDIR}

${BUILDDIR}/%.o: ${SRCDIR}/%.c
	$(CC) ${CFLAGS} ${IFLAGS} -o $(subst /,${SEP},$@) -c $(subst /,${SEP},$<)

${TARGET}: directories ${OBJS}
	ar rcs ${TARGET} ${OBJS}
	ranlib ${TARGET}

clean:
	$(RM) ${BUILDDIR}

fclean: clean
	$(RM) ${LIBDIR}
	$(RM) a.out

re: fclean all

examples: $(TARGET)
	@$(CC) ${CFLAGS} ${IFLAGS} -L${LIBDIR} ${EXAMPLESDIR}/tests.c -o a.out -lcunits42

run-examples: examples
	@./a.out

.PHONY: clean fclean examples re run-examples directories build
