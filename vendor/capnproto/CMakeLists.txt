CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 68bd4790621a77f30b5f7dbd13ad1e8fc5f8bda0
    OPTIONS "BUILD_TESTING OFF" "CMAKE_CXX_EXTENSIONS ON" "CMAKE_C_EXTENSIONS ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_capnproto
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE capnp-rpc)
