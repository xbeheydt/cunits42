# tests/CMakeList.txt : CMake project for tests, include source and define
# project specific logic here.
#

set(
	HEADER_FILE_TESTS
	"${PROJECT_SOURCE_DIR}/tests/.tests.h"
)
set(
	SOURCE_FILE_TESTS
	"${PROJECT_SOURCE_DIR}/tests/.tests.c"
	"${PROJECT_SOURCE_DIR}/tests/.test_main.c"
	#Add others test sources
)


if($ENV{INTERNAL})
	message("INTERNAL defined")
	add_compile_definitions(INTERNAL=1)
endif()
if($ENV{MANDATORY})
	message("MANDATORY defined")
	add_compile_definitions(MANDATORY=1)
endif()
if($ENV{BONUS})
	message("BONUS defined")
	add_compile_definitions(BONUS=1)
endif()


# Create tests executable
add_executable(
	${PROJECT_NAME}-tests
	${HEADER_FILE_TESTS}
	${SOURCE_FILE_TESTS}
	${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}-tests ${LIBS})
target_include_directories(
	${PROJECT_NAME}-tests
	PRIVATE
	"${PROJECT_SOURCE_DIR}/tests"
	"${INCLUDES}"
)

# IDE tree view
source_group(
	"Header_Files"
	FILES ${HEADER_FILE_TESTS}
)

source_group(
	"Source_Files"
	FILES ${SOURCE_FILE_TESTS}
)

# tests section
add_test(test_your_fcn ${PROJECT_NAME}-tests -t test_your_fcn)
set_tests_properties(test_your_fcn PROPERTIES WILL_FAIL TRUE)
set_tests_properties(test_your_fcn PROPERTIES PASS_REGULAR_EXPRESSION "KO")
