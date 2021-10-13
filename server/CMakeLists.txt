cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(protei-server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(protei-server server.cpp server.h
        algorithm/algo.h)