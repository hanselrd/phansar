CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG c056a009de3404caaf9d5f477cb6bb65c4b7ca61
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_fmt
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE fmt)
