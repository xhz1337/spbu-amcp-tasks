cmake_minimum_required(VERSION 3.31.5)

project(project)

set(CMAKE_CXX_STANDARD 17)

enable_testing()	
add_subdirectory(lib/googletest)

add_subdirectory(menu)
add_subdirectory(sorting)

include_directories(menu)
include_directories(sorting)