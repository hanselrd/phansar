CPMAddPackage(
    NAME range-v3
    GITHUB_REPOSITORY ericniebler/range-v3 # master
    GIT_TAG c097c0e8d1378d95763426f024fbfeea745b4093
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_rangev3
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE range-v3)
