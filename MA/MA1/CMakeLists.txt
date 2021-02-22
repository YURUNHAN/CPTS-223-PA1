cmake_minimum_required(VERSION 3.0)
project(MicroAssignment1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

add_executable(MicroAssignment1 main.cpp testQueue.cpp)

