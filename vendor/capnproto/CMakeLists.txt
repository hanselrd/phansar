CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 80758f9cbd27940704e175aecf6f619aa098c8c0
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
