PROJECT		= cunits42

SRCDIR		= ${CURDIR}/src
HEADERDIR	= ${CURDIR}/include/${PROJECT}

BUILDDIR	= ${CURDIR}/build
INCLUDEDIR	= ${BUILDDIR}/include
LIBDIR		= ${BUILDDIR}/lib
BINDIR		= ${BUILDDIR}/bin

LIB			= ${LIBDIR}/lib${PROJECT}.a

SRCS		= ${SRCDIR}/cunits42.c
OBJS		= $(subst ${SRCDIR},${BUILDDIR}/src, ${SRCS:.c=.o})

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g3
IFLAGS		= -Iinclude/${PROJECT} -Isrc

RM		= rm -rf
MKDIR	= mkdir -p

.PHONY:	directories clean fclean example  install

all: directories ${LIB}

directories:
	@$(MKDIR) ${BUILDDIR}
	@$(MKDIR) ${BUILDDIR}/src
	@$(MKDIR) ${INCLUDEDIR}
	@$(MKDIR) ${LIBDIR}
	@$(MKDIR) ${BINDIR}

${BUILDDIR}/src/%.o: ${SRCDIR}/%.c
	$(CC) ${CFLAGS} ${IFLAGS} -o $@ -c $<

$(LIB): directories ${OBJS}
	cp ${HEADERDIR}/*.h ${INCLUDEDIR}
	ar rcs $@ ${OBJS}
	ranlib $@

clean:
	$(RM) ${OBJS}

fclean: clean
	$(RM) ${BUILDDIR}

re: fclean all

test: $(LIB)
	$(CC) ${CFLAGS} ${IFLAGS} -L${LIBDIR} ${CURDIR}/example/example.c \
		-o ${BINDIR}/example -l${PROJECT}

install:
	install -D ${BUILDDIR}/include/*.h ${CURDIR}/include
	install -D ${BUILDDIR}/lib/* ${CURDIR}/lib
