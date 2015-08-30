cmake_minimum_required (VERSION 2.8)

set (zeno_VERSION_MAJOR 1)
set (zeno_VERSION_MINOR 0)

SET( CMAKE_OSX_ARCHITECTURES "x86_64" )

# to add custom flags
# add_definitions(${GCC_COMPILE_FLAGS})
# SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

project (zeno)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory (zeno_common)
include_directories (zeno_common)

add_executable(zeno $<TARGET_OBJECTS:zeno_common> main.cpp)
