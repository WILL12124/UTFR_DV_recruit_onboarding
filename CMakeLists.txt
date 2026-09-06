cmake_minimum_required(VERSION 3.10)
project(cone_path_traversal CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(run_tests
    src/solution.cpp
    src/track_generator.cpp
    src/svg_plot.cpp
    src/tests.cpp
    src/run_tests.cpp
)
