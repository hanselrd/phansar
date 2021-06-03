CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 32b47ec74b4d2acdac241a9cd6b12383983f57d0
    OPTIONS "BUILD_TESTING OFF" "CMAKE_CXX_EXTENSIONS ON" "CMAKE_C_EXTENSIONS ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_capnproto
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE capnp-rpc)
