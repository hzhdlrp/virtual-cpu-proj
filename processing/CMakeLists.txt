cmake_minimum_required(VERSION 3.26)
project(processing CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(processing INTERFACE commands.hpp processing.hpp)