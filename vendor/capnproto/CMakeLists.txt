CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 2670d0cebd7f1d8d9cdc4e68f42ba3e971f7fd12
    OPTIONS "BUILD_TESTING OFF" "CMAKE_CXX_EXTENSIONS ON" "CMAKE_C_EXTENSIONS ON")

# cmake-format: off
set(system_libs
    capnp-rpc)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_capnproto
    ""
    ""
    "${system_libs}")
