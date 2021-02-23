CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 7a31fa889d13286f02a19444e7073d12a6e773c7
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
