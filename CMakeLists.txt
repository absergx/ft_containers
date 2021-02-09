cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
add_compile_options( -Wall -Wextra -Werror -Wconversion -Wno-unused)


set(INCLUDE_DIRS srcs)

include_directories(${INCLUDE_DIRS})

set(SRCS
		srcs/list.hpp
#        srcs/iterator.hpp
        srcs/vector.hpp
        srcs/map.hpp
#        srcs/stack.hpp
        srcs/queue.hpp)

add_executable(ft_containers main.cpp ${SRCS})
add_executable(jalvaro_tests jalvaro_tests/main.cpp jalvaro_tests/map_test.cpp jalvaro_tests/list_test.cpp jalvaro_tests/queue_test.cpp jalvaro_tests/stack_test.cpp jalvaro_tests/vector_test.cpp)

add_library(testlib INTERFACE)
target_include_directories(testlib INTERFACE ./srcs)
add_subdirectory(unit_tests)