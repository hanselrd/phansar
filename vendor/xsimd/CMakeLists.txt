CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 4c3c7f850c8c925e44f5b0670df8f543e62aeb12
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_xsimd
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE xsimd)
