cmake_minimum_required(VERSION 3.14)
project(obman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(Utils.cmake)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    init_debug()
endif()

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

add_subdirectory(object_manager)
#add_subdirectory(obman_php)
#add_subdirectory(tests)