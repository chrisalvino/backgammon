cmake_minimum_required (VERSION 2.8)

# set (zeno_VERSION_MAJOR 0)
# set (zeno_VERSION_MINOR 1)

SET( CMAKE_OSX_ARCHITECTURES "x86_64" )

# to add custom flags
# add_definitions(${GCC_COMPILE_FLAGS})
# SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror " )

project (zeno)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory (zeno_common)
add_subdirectory (display)

include_directories (zeno_common)
include_directories (display)

add_executable(zeno $<TARGET_OBJECTS:zeno_common> $<TARGET_OBJECTS:display> main.cpp)
