cmake_minimum_required(VERSION 3.5)
project(libdsa C)

# Set the C standard required
set(CMAKE_C_STANDARD 11)
# set clang-format flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set cmake debug target
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS 
	"${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wuninitialized \
	-Wmissing-prototypes")

# Ensure the build directory exists
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# Library
file(GLOB_RECURSE SOURCES "src/*.c")
add_library(dsa STATIC ${SOURCES})
target_include_directories(dsa PUBLIC include/)

# Tests
enable_testing()
file(GLOB_RECURSE TEST_SOURCES "tests/*.c")
add_executable(dsa_test ${TEST_SOURCES})
target_link_libraries(dsa_test dsa)
add_test(NAME dsa_test COMMAND dsa_test)

