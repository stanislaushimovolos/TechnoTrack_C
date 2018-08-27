cmake_minimum_required(VERSION 3.10)
project(HashTables)

set(CMAKE_CXX_STANDARD 11)

include_directories(${SFML_INCLUDE_DIR})

add_executable(HashTables main.cpp HashTable.hpp List_t/List.h WorkWithFiles/WorkWithFiles.h WorkWithFiles/WorkWithFiles.cpp HashFunctions/HashFunctions.cpp HashFunctions/HashFunctions.h)