CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 0799703097ee1271fa4c38051f27b5ec9601b891
    OPTIONS "BUILD_TESTING OFF" "CMAKE_CXX_EXTENSIONS ON" "CMAKE_C_EXTENSIONS ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_capnproto
    TYPE INTERFACE
    LINK_LIBRARIES
        SYSTEM
        INTERFACE
        capnp
        capnp-json)
