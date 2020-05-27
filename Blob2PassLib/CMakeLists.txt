set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabi-g++")

project(Blob2PassLib)

set(CMAKE_BUILD_TYPE "Debug")

# add_library(Blob2PassLib SHARED
#     blob2pass.cc
# )

add_library(Blob2PassLib
    blob2pass.cc
)

set_target_properties(Blob2PassLib PROPERTIES PUBLIC_HEADER blob2pass.hh)

# target_include_directories(Blob2PassLib
#     PRIVATE 
#         .
#     INTERFACE
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#     $<INSTALL_INTERFACE:include>
# )