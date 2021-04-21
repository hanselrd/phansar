CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts # master
    GIT_TAG 174510285a451d5e2ab2c4054bc88ce8b4ba933d
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_cxxopts
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE cxxopts)
