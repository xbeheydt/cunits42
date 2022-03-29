# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (
	"cuntis42"
	VERSION 0.1.0
)
enable_testing()

add_subdirectory(tests)
# add other subdirectories HERE

set(
	HEADER_FILES
	# your headers files
) 
set(
	SOURCE_FILES
	# your sources files
)

set(
	LIBS
	# your libs
)

set(
	INCLUDES
	"${PROJECT_SOURCE_DIR}/include"
	# other include folders
)

# Create static lib target
add_library(libft STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(libft PRIVATE libft)
target_include_directories(
	libft
	PUBLIC
	"${INCLUDES}"
)

# Create executable target
add_executable(exe ${HEADER_FILE_TESTS} ${SOURCE_FILES} "${PROJECT_SOURCE_DIR}/src/main.c")
target_link_libraries(exe PRIVATE libft)
target_include_directories(
	exe
	PRIVATE
	"${INCLUDES}"
)

# IDE tree view
source_group(
	"Header_Files"
	FILES ${HEADER_FILES}
)

source_group(
	"Source_Files"
	FILES ${SOURCE_FILES}
)
