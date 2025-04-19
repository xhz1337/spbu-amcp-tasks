add_executable(mmh_test test_long_number.cpp)
target_link_libraries(mmh_test
    gtest_main
    ${LONG_NUMBER_LIB}
)
add_test(mmh_test mmh_test)
