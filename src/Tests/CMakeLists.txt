cmake_minimum_required(VERSION 3.1)
project(UnitTesting CXX)
set(CMAKE_CXX_STANDARD 11)	
set(CMAKE_CXX_COMPILER g++)

include(CTest)
include(GoogleTest)
enable_testing()

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(UnitTesting ${TEST_SOURCES})

target_link_libraries(UnitTesting PUBLIC gtest_main Core Chip8)
gtest_discover_tests(UnitTesting)