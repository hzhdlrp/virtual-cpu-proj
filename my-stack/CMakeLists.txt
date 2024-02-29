cmake_minimum_required(VERSION 3.26)
project(stack)


set(CMAKE_CXX_STANDARD 20)

add_library(mylib STATIC Stack.hpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/my-stack")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest")

target_include_directories(tests PUBLIC "${gtest_SOURCE_DIR}/include")

add_executable(tests tests.cpp)

target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests my-stack)

