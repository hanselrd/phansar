CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 74959a87c8a95de6f8e636de92c123b2a538809f
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_xsimd
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE xsimd)
