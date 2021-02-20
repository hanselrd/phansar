CPMAddPackage(
    NAME enet
    GITHUB_REPOSITORY lsalzman/enet # master
    GIT_TAG e3ada4ed750b976833e3d54a9c1179445289bbf6
    OPTIONS "CMAKE_POLICY_DEFAULT_CMP0048 NEW")

# cmake-format: off
set(includes
    ${enet_SOURCE_DIR}/include)

set(system_libs
    enet)
if(WIN32)
    set(system_libs
        ${system_libs}
        ws2_32
        winmm)
endif()
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_enet
    "${includes}"
    ""
    "${system_libs}")
