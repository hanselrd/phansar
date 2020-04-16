# cmake-format: off
# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_mixer REQUIRED)
# find_package(SDL2_ttf REQUIRED)

set(sources
    main.cpp)

set(libs
    ph_common
    ph_vendor_raygui
    ph_vendor_raylib)

# set(system_libs
#     SDL2::Core
#     SDL2::Image
#     SDL2::Mixer
#     SDL2::TTF)
# cmake-format: on

# ph_add_generic_executable(ph_client "${sources}" "${libs}" "${system_libs}")
ph_add_generic_executable(ph_client "${sources}" "${libs}" "")
