cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wfloat-conversion -Werror -pedantic")

# ----- tests -----
add_executable(algo-test-str get_nums_from_str.cpp)
add_executable(algo-test-sum vector_sum.cpp)
add_executable(algo-test-num is_number.cpp)

add_test(NAME algo-test-str COMMAND algo-test-str)
add_test(NAME algo-test-sum COMMAND algo-test-sum)
add_test(NAME algo-test-num COMMAND algo-test-num)