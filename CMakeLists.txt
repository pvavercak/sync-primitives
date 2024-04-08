cmake_minimum_required(VERSION 3.23)

project(SYNC_PRIMITIVES VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sync INTERFACE)
add_library(pva::sync ALIAS sync)
target_sources(sync INTERFACE
    FILE_SET HEADERS
    FILES
    include/sync/mutex.hpp
    BASE_DIRS
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(TARGETS sync FILE_SET HEADERS DESTINATION include)

enable_testing()
add_subdirectory(tests)
