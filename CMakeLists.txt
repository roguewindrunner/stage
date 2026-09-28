cmake_minimum_required(VERSION 3.25)
project(Stage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Core library (shared by game and tests) ---
add_library(stage_core src/core/math_utils.cpp)
target_include_directories(stage_core PUBLIC src)

# --- The game ---
add_executable(stage src/main.cpp)
target_link_libraries(stage PRIVATE stage_core)

# --- Tests ---
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(stage_tests tests/math_utils_test.cpp)
target_link_libraries(stage_tests PRIVATE stage_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(stage_tests)