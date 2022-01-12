CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY bkaradzic/bgfx.cmake # master
    GIT_TAG 7e7a6795a1ce50f41249efd136385a8266831360
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_bgfx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE bgfx)
