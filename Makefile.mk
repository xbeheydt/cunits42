ARGS	?=
dbgtests: CFLAGS += ${CDEBUG}
dbgtests: $(NAME)
	@$(MKDIR) ${EXE_DIR}
	@$(CC) -w ${ITESTS} ${LFLAGS} -o ${EXE_DIR}/tests ${SRCS_TEST} ${LKFLAGS}
	@$(GDB) ${EXE_DIR}/tests ${ARGS}

tests: $(NAME)
	@$(MKDIR) ${EXE_DIR}
	@$(CC) -w ${ITESTS} ${LFLAGS} -o ${EXE_DIR}/tests ${SRCS_TEST} ${LKFLAGS}
	@${EXE_DIR}/tests ${ARGS}

ctest:
	@$(MKDIR) ${BUILD_DIR}; cd ${BUILD_DIR}; cmake ..; make 42cursus-libft-tests; ctest $(ARGS)
