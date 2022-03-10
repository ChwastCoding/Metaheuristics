cmake_minimum_required(VERSION 3.0.0)

set(testname tests)

set(sources
    setup_test.cpp
)

add_executable(${testname} ${sources})
target_link_libraries(${testname} PUBLIC gtest_main)

add_test(
    NAME ${testname}
    COMMAND ${testname}
)