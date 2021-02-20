CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY pr0g/bgfx.cmake # main
    GIT_TAG e909b52676d3ea05c7f156b4b43a6e4d5abd5d78)

# cmake-format: off
set(system_libs
    bgfx)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_bgfx
    ""
    ""
    "${system_libs}")
