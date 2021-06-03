CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts # master
    GIT_TAG df229cff0d5b96e146f3f11441f714e8e240cad0
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_cxxopts
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE cxxopts)
