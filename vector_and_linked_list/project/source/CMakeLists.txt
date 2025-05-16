set(SOURCE_VECTOR vector.cpp)
set(SOURCE_LINKED_LIST linked_list.cpp)

set(HEADER_VECTOR vector.hpp)
set(HEADER_LINKED_LIST linked_list.hpp)

add_library(${VECTOR_LIB} ${HEADER_VECTOR} ${SOURCE_VECTOR})   
add_library(${LINKED_LIST_LIB} ${HEADER_LINKED_LIST} ${SOURCE_LINKED_LIST})   


target_include_directories(${VECTOR_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${LINKED_LIST_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

