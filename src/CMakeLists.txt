# cunits42/CMakeList.txt : CMake project for cunits42, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(HEADER_FILES "${cunits42_SOURCE_DIR}/include/cunits42/cunits42.h")
set(HEADER_INTERNAL_FILES "${cunits42_SOURCE_DIR}/src/cunits42_internal.h")
set(SOURCE_FILES "${cunits42_SOURCE_DIR}/src/cunits42.c")

# Add source to this project's library.
add_library(
	cunits42
	SHARED
	${SOURCE_FILES}
	${HEADER_FILES}
	${HEADER_INTERNAL_FILES}
)
target_include_directories(
	cunits42
	PUBLIC
	"${cunits42_SOURCE_DIR}/include/cunits42"
)

# Install target
install(TARGETS cunits42 DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)

# IDE tree view
source_group(
	"Header_Files"
	FILES ${HEADER_FILES} ${HEADER_INTERNAL_FILES}
)

source_group(
	"Source_Files"
	FILES ${SOURCE_FILES}
)
