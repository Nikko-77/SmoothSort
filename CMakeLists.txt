cmake_minimum_required(VERSION 3.15)

project(SmoothSort)

find_package(OpenMP REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(SmoothSort "main.cc")
target_link_libraries(SmoothSort OpenMP::OpenMP_CXX)
