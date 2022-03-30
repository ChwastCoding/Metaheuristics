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
        ../src/solver/K_RandomSolver.cpp ../src/solver/NearestNeighbour.cpp ../src/solver/ExtNearestNeighbour.cpp ../src/solver/Solver.cpp
)

set(headers
     ../src/tsp_data/Euc2DInstance.h
     ../src/tsp_data/MatrixInstance.h
     ../src/tsp_data/TSPInstance.h
     ../src/tsp_data/ProblemFactory.h
    ../src/util.h
        ../src/solver/NearestNeighbour.h
        ../src/solver/K_RandomSolver.h
        ../src/solver/ExtNearestNeighbour.h
        ../src/solver/Solver.h
)

add_executable(${testname} ${sources} ${headers})
target_link_libraries(${testname} PUBLIC gtest_main)

add_test(
    NAME ${testname}
    COMMAND ${testname}
)