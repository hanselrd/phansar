project(${CMAKE_PROJECT_NAME})

set(sources
    managers/system_manager.cpp)

set(libs
    common)

add_executable(${PROJECT_NAME}
    ${sources}
    main.cpp)

target_link_libraries(${PROJECT_NAME}
    ${libs})

add_library(${PROJECT_NAME}-test STATIC
    ${sources})

target_include_directories(${PROJECT_NAME}-test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}-test PUBLIC
    ${libs})
