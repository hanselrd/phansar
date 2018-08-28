project(tools)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools)

set(libs
    common)

add_executable(compile_assets
    compile_assets.cpp)

target_link_libraries(compile_assets
    ${libs})
