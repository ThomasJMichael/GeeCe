cmake_minimum_required(VERSION 3.16)

project(GeeCe C)

# Compiler and linker options
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic -O2")

# Directories
set(INC_DIR include)
set(SRC_DIR src)
set(OBJ_DIR obj)
set(BIN_DIR bin)
set(TEST_DIR tests)

# Targets
set(TARGET ${BIN_DIR}/geece)
set(TEST_TARGET ${BIN_DIR}/test_gc)

# Sources and objects
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE TEST_SOURCES "${TEST_DIR}/*.c")
set(OBJECTS ${SOURCES})
set(TEST_OBJECTS ${TEST_SOURCES})

# Includes
include_directories(${INC_DIR})

# Unity
include_directories(${INC_DIR}/Unity)
set(UNITY_SOURCES ${INC_DIR}/Unity/unity.c)
list(APPEND OBJECTS ${UNITY_SOURCES})

# Rules
add_executable(${TARGET} ${OBJECTS})
add_executable(${TEST_TARGET} ${TEST_OBJECTS} ${UNITY_SOURCES})
target_compile_definitions(${TEST_TARGET} PRIVATE UNIT_TESTING)

# Clean
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${TARGET} ${TEST_TARGET})

# Tests
enable_testing()
add_test(NAME GeeCeTests COMMAND ${TEST_TARGET})
