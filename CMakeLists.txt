cmake_minimum_required(VERSION 3.23)
project(Project1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(Project1 main.cpp offsets.hpp memory_controller.h memory_controller.cpp include.h vector.h config.h colors.h hacks.cpp hacks.h)