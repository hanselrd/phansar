CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts # master
    GIT_TAG e9d20c2c078076da928288fdbae2a39431b4f253
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_cxxopts
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE cxxopts)
