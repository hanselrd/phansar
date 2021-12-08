CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts # master
    GIT_TAG ad2d1a6b5fd3fbb7bb0e7bc11f28a427494aea45
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_cxxopts
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE cxxopts)
