cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(protei)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(protei-main main.cpp)

add_subdirectory(server)
add_subdirectory(client)