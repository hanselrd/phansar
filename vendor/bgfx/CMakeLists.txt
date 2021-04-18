CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY widberg/bgfx.cmake # master
    GIT_TAG 66f18daf5c380b34f4745ac0922b8a9853b51ad9
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_bgfx
    TYPE INTERFACE
    LINK_LIBRARIES INTERFACE bgfx)
