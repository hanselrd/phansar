CPMAddPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3 # master
    GIT_TAG b0696c75dd8b420432c76e5d90fa133ccb423437
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_rangev3
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE range-v3)
