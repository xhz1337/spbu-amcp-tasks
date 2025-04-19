cmake_minimum_required(VERSION 3.31.5)

project(ln)

set(CMAKE_CXX_STANDARD 17)
	
enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(source)
include_directories(source)