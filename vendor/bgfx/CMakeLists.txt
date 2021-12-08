CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY bkaradzic/bgfx.cmake # master
    GIT_TAG a01e8e043fe213a55b0bea9623f45fad80d067bc
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_bgfx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE bgfx)
