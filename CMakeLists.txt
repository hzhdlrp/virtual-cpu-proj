cmake_minimum_required(VERSION 3.26)
project(project2)

set(CMAKE_CXX_STANDARD 20)

add_executable(project2 main.cpp
)

add_subdirectory(my-stack)
target_link_libraries(project2 mylib)
