
file(GLOB SOURCE_CPP_FILES "*.cpp")

include_directories (../zeno_common)

add_library (display OBJECT ${SOURCE_CPP_FILES})

target_include_directories (display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})