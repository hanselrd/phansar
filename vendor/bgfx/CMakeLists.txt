CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY widberg/bgfx.cmake # master
    GIT_TAG 66f18daf5c380b34f4745ac0922b8a9853b51ad9)

# cmake-format: off
set(system_libs
    bgfx)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_bgfx
    ""
    ""
    "${system_libs}")
