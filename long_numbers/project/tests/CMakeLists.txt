add_executable(mmh_test test_long_number.cpp)
target_link_libraries(mmh_test
    gtest_main
    long_numbers
)
add_test(mmh_test mmh_test)
