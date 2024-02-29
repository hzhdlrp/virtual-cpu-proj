cmake_minimum_required(VERSION 3.26)
project(project2)

set(CMAKE_CXX_STANDARD 20)

add_executable(project2 main.cpp)

target_include_directories(project2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/my-stack")

add_subdirectory(my-stack)
target_link_libraries(project2 mylib)
