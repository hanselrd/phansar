CPMAddPackage(
    NAME capnproto
    GITHUB_REPOSITORY capnproto/capnproto # master
    GIT_TAG 45b8c519aef9a0b40d8bbcacbb557cf47ed19809
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
