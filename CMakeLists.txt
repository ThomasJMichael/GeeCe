cmake_minimum_required(VERSION 3.24)
project(GeeCe C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(GeeCe
        include/configuration.h
        include/geece.h
        include/heap.h
        include/logger.h
        include/mark_and_sweep.h
        include/object.h
        include/reference.h
        include/reference_counting.h
        include/timer.h
        include/utils.h
        src/configuration.c
        src/geece.c
        src/heap.c
        src/logger.c
        src/mark_and_sweep.c
        src/object.c
        src/reference.c
        src/reference_counting.c
        src/timer.c
        src/utils.c
        tests/test_geece.c
        tests/test_heap.c
        tests/test_object.c
        tests/test_reference.c
        tests/unity.c
        include/root_table.h
        src/root_table.c
        tests/test_root_table.c)
