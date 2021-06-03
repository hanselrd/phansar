CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY widberg/bgfx.cmake # master
    GIT_TAG eebff97af2a34c695cdc058c63ba527c6ebebc76
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_bgfx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE bgfx)
