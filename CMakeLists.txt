cmake_minimum_required(VERSION 3.0.0)
project(Metaheurisitics VERSION 0.1.0)

enable_testing()

add_subdirectory(googletest)

set (headers
    # add headers here
)

set (sources
    # add sources here
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${headers} ${sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(tests)