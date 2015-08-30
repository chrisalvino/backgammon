
file(GLOB SOURCE_CPP_FILES "*.cpp")

add_library (zeno_common OBJECT ${SOURCE_CPP_FILES})

target_include_directories (zeno_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})