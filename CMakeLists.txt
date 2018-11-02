cmake_minimum_required(VERSION 3.12)
project(Threads)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(Threads main.cpp)