
file(GLOB SOURCE_CPP_FILES "*.cpp")

include_directories (../zeno_common)
add_library (zeno_test OBJECT ${SOURCE_CPP_FILES})

target_include_directories (zeno_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})