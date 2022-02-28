# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (
	"cunits42"
	VERSION 0.1.0
)

# Include sub-projects.
add_subdirectory("src")
add_subdirectory("example")
