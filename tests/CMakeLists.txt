cmake_minimum_required(VERSION 3.0.0)

set(testname tests)

set(sources
    setup_test.cpp
    ../src/tsp_data/Euc2DInstance.cpp
    ../src/tsp_data/TSPInstance.cpp
    ../src/tsp_data/MatrixInstance.cpp
    ../src/tsp_data/Parser.cpp
    ../src/tsp_data/ProblemFactory.cpp
    ../src/util.cpp
)

set(headers
     ../src/tsp_data/Euc2DInstance.h
     ../src/tsp_data/MatrixInstance.h
     ../src/tsp_data/TSPInstance.h
     ../src/tsp_data/ProblemFactory.h
    ../src/util.h
)

add_executable(${testname} ${sources} ${headers})
target_link_libraries(${testname} PUBLIC gtest_main)

add_test(
    NAME ${testname}
    COMMAND ${testname}
)