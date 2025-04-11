cmake_minimum_required(VERSION 3.31.5)

project(ln)

set(CMAKE_CXX_STANDARD 17)
	
add_executable(main main.cpp)
add_subdirectory(source)
include_directories(source)