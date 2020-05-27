cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabi-g++")

set(CMAKE_CXX_FLAGS "-O2")

project(Blob2Pass LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Debug")

include_directories(Blob2PassLib)
add_executable(Blob2Pass execute.cc)

add_subdirectory(Blob2PassLib)

target_link_libraries(Blob2Pass PUBLIC Blob2PassLib)
