cmake_minimum_required(VERSION 3.26)
project(stack CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(mylib INTERFACE Stack.hpp)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest")

add_executable(tests tests.cpp)

target_include_directories(tests PUBLIC "${gtest_SOURCE_DIR}/include")

target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests my-stack)

