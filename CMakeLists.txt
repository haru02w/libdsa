cmake_minimum_required(VERSION 3.0)
project(libdsa C)

# Set the C standard required
set(CMAKE_C_STANDARD 11)
# clang-format flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

