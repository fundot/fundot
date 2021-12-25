cmake_minimum_required(VERSION 3.10)

project(Fundot)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(core)

add_subdirectory(std)

add_subdirectory(repl)
