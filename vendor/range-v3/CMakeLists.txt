CPMAddPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3 # master
    GIT_TAG b832d51e2f796a31011e11d4a072941e61d27772
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_rangev3
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE range-v3)
