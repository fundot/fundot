cmake_minimum_required(VERSION 3.10)

project(Fundot)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_USE_STATIC_LIBS ON)

set(Boost_USE_DEBUG_LIBS OFF)

set(Boost_USE_RELEASE_LIBS ON)

set(Boost_USE_MULTITHREADED ON)

set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.67.0 REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(include)

add_subdirectory(src)

add_subdirectory(tests)
