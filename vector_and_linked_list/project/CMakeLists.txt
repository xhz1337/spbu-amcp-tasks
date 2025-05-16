cmake_minimum_required(VERSION 3.31.5)
set(CMAKE_CXX_STANDARD 17)

project(vector_and_linked_list)

set(VECTOR_LIB "vector_lib")
set(LINKED_LIST_LIB "linked_list_lib")
	
enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(source)
add_subdirectory(tests)