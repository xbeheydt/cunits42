INCLUDE_PATH	= ./include
SRC_PATH		= ./src

CUNITS42_SRCS	= ${SRC_PATH}/cunits42.c
CUNITS42_INC	= -I${INCLUDE_PATH}


MEMTRACE_SRCS	= ${SRC_PATH}/memtrace.c
MEMTRACE_INC	= -I${INCLUDE_PATH} -I{SRC_PATH}
MEMTRACE_LNK	= -ldl -lmcheck	


CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -g3
RM				= rm -rf
