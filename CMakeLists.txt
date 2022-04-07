cmake_minimum_required(VERSION 3.0.0)
project(Metaheurisitics VERSION 0.1.0)

enable_testing()

add_subdirectory(googletest)

set (headers
    src/util.h
    src/solver/Solver.h
    src/solver/DummySolver.h
    src/solver/TwoOptSolver.h
    src/visualization/Visualization.h
    src/tsp_data/Euc2DInstance.h
    src/tsp_data/MatrixInstance.h
    src/tsp_data/TSPInstance.h
    src/tsp_data/Parser.h
    src/tsp_data/ProblemFactory.h
    src/solver/NearestNeighbour.h
    src/solver/K_RandomSolver.h
    src/solver/ExtNearestNeighbour.h
)

set (sources
    src/util.cpp
    src/solver/Solver.cpp
    src/solver/DummySolver.cpp
    src/solver/TwoOptSolver.cpp
    src/visualization/Visualization.cpp
    src/main.cpp
    src/tsp_data/TSPInstance.cpp
    src/tsp_data/Euc2DInstance.cpp
    src/tsp_data/MatrixInstance.cpp
    src/tsp_data/Parser.cpp
    src/tsp_data/ProblemFactory.cpp
    src/solver/K_RandomSolver.cpp
    src/solver/NearestNeighbour.cpp
    src/solver/ExtNearestNeighbour.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_package(SFML 2 COMPONENTS graphics window audio REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/lib_mingw/cmake/SFML")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(SFML 2 COMPONENTS graphics window audio REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/lib_gcc/cmake/SFML")
endif()

add_executable(${PROJECT_NAME} ${headers} ${sources})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(tests)