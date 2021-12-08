CPMAddPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3 # master
    GIT_TAG 83783f578e0e6666d68a3bf17b0038a80e62530e
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_rangev3
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE range-v3)
