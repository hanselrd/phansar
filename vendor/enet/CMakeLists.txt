CPMAddPackage(
    NAME enet
    GITHUB_REPOSITORY lsalzman/enet # master
    GIT_TAG 987cd0650f887033c8b1450f771763639bcbb111
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
