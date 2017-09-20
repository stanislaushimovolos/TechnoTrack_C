cmake_minimum_required(VERSION 3.8)
project(shakespeare)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp shakspeare.cpp shakspeare.h)
add_executable(shakespeare ${SOURCE_FILES})