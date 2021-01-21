cmake_minimum_required(VERSION 3.10)

project(Fundot)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system filesystem)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(include)

add_subdirectory(objects)

add_subdirectory(src)

add_subdirectory(tests)

install(FILES init.fun DESTINATION fundot)

include(InstallRequiredSystemLibraries)

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

include(CPack)
