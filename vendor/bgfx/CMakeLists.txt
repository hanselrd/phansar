CPMAddPackage(
    NAME bgfx
    GITHUB_REPOSITORY bkaradzic/bgfx.cmake # master
    GIT_TAG b44793b740ec6473ec1739e7b0bc07de838c76af
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_bgfx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE bgfx)
