CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 8c758e83cd2a95eaac431a5efd50fdb2a0f0c77d
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_xsimd
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE xsimd)
