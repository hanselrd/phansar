CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG d4a3770452a9f1e470788a4e5b12388f101b14e1
    OPTIONS "BUILD_TESTING OFF" "CMAKE_CXX_EXTENSIONS ON" "CMAKE_C_EXTENSIONS ON"
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(system_libs
    capnp-rpc)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_capnproto
    ""
    ""
    "${system_libs}")
