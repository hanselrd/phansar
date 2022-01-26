CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 315f7c11751bab0771478f48c4197b4cf9b50404
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_xsimd
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE xsimd)
