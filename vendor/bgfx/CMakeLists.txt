CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY bkaradzic/bgfx.cmake # master
    GIT_TAG 3168a4660eb44174830ecd723907c19805342e93
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_bgfx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE bgfx)
