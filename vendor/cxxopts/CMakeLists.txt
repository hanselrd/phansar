CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts # master
    GIT_TAG 4e208b95b7ae488b0d31fcc80228b141792b79b5
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_cxxopts
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE cxxopts)
