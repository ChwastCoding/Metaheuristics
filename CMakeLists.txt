cmake_minimum_required(VERSION 3.0.0)
project(Metaheurisitics VERSION 0.1.0)

enable_testing()

add_subdirectory(googletest)

set (headers
    src/util.h
    src/solver/Solver.h
    src/solver/DummySolver.h
    src/visualization/Visualization.h
    src/tsp_data/Euc2DInstance.h
    src/tsp_data/MatrixInstance.h
    src/tsp_data/TSPInstance.h
    src/tsp_data/ProblemFactory.h
)

set (sources
    src/util.cpp
    src/solver/Solver.cpp
    src/solver/DummySolver.cpp
    src/visualization/Visualization.cpp
    src/main.cpp
    src/tsp_data/Euc2DInstance.cpp
    src/tsp_data/MatrixInstance.cpp
    src/tsp_data/TSPInstance.cpp
    src/tsp_data/ProblemFactory.cpp
        src/solver/K_RandomSolver.h src/solver/K_RandomSolver.cpp src/solver/NearestNeighbour.cpp src/solver/NearestNeighbour.h src/solver/ExtNearestNeighbour.cpp src/solver/ExtNearestNeighbour.h)

find_package(SFML 2 COMPONENTS graphics window audio REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake/SFML")

add_executable(${PROJECT_NAME} ${headers} ${sources})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(tests)