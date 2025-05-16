include(GoogleTest)

add_executable(vec_test test_vector.cpp)
add_executable(linked_list_test test_linked_list.cpp)

target_link_libraries(vec_test
    gtest_main
    ${VECTOR_LIB}
)

target_link_libraries(linked_list_test
    gtest_main
    ${LINKED_LIST_LIB}
)

gtest_discover_tests(vec_test)
gtest_discover_tests(linked_list_test)


