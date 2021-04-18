CPMAddPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3 # master
    GIT_TAG 1120609c7cb5dee9d2d216c579e935475cc39c4e
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_rangev3
    TYPE INTERFACE
    LINK_LIBRARIES INTERFACE range-v3)
