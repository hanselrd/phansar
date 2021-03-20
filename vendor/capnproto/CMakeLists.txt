CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG e32eaad6d3c78f8e11e4ba86ce4eedc339ec54cf
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
