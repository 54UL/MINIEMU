cmake_minimum_required(VERSION 3.1)
project(UnitTesting CXX)
set(CMAKE_CXX_STANDARD 11)	
set(CMAKE_CXX_COMPILER g++)

include(CTest)
include(GoogleTest)
enable_testing()

set(RUNNING_TESTS_SOURCES
#    Chip8_TEST.cpp
   GameBoy_TEST.cpp
   )


add_executable(UnitTesting ${RUNNING_TESTS_SOURCES})

target_link_libraries(UnitTesting PUBLIC gtest_main Core Chip8 GameBoy)
gtest_discover_tests(UnitTesting)