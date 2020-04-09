find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# cmake-format: off
set(sources
    main.cpp)

set(libs
    ph_common)

set(system_libs
    SDL2::Core
    SDL2::Image
    SDL2::Mixer
    SDL2::TTF)
# cmake-format: on

ph_add_generic_executable(ph_client "${sources}" "${libs}" "${system_libs}")
