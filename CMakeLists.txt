cmake_minimum_required(VERSION 3.22)

project(dualshock4_cpp)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(HIDAPI REQUIRED)

include_directories(include src)
add_executable(dualshock4_cpp src/main.cpp)

target_link_libraries(dualshock4_cpp PRIVATE HIDAPI::hidapi)