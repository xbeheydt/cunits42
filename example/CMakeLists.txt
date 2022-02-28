# example/CMakeList.txt : CMake project for cunits42-example,
# include source and define project specific logic here.
#

set(SOURCE_FILES "${PROJECT_SOURCE_DIR}/example/example.c")
add_executable(example ${SOURCE_FILES})
target_link_libraries(example PRIVATE cunits42)

# Instal target
install(TARGETS example DESTINATION bin)

# IDE tree view
source_group(
	"Source_Files"
	FILES ${SOURCE_FILES}
)

enable_testing()
add_test(NAME Run COMMAND example)