CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 394baa44ccf0aee94871644eaec9a9fb3819d258
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_xsimd
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE xsimd)
