CPMAddPackage(
    NAME enet
    GITHUB_REPOSITORY lsalzman/enet # master
    GIT_TAG 498b9e3571c2e096d7143c3c76852c5ec28d7885
    OPTIONS "CMAKE_POLICY_DEFAULT_CMP0048 NEW")

ph_add_library(
    NAME ph_vendor_enet
    TYPE INTERFACE
    INCLUDE_DIRECTORIES SYSTEM INTERFACE ${enet_SOURCE_DIR}/include
    LINK_LIBRARIES
        SYSTEM
        INTERFACE
        enet
        $<$<BOOL:${WIN32}>:ws2_32>
        $<$<BOOL:${WIN32}>:winmm>)
