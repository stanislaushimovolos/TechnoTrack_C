cmake_minimum_required(VERSION 3.8)
project(Akinator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Akinator/main.cpp Fileworking/fileworking.h Tree_t/Tree.cpp Tree_t/Tree.h Akinator/Akinator.h)
add_executable(Akinator ${SOURCE_FILES} Tree_t/Tree.cpp Tree_t/Tree.h)
