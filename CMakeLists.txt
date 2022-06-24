cmake_minimum_required(VERSION 3.22)
project(dualshock4_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)

add_executable(dualshock4_cpp src/main.cpp)
