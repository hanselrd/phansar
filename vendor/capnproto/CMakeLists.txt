CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 767b8a30ee100f1c648a75c9aaf252212d904c17
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
