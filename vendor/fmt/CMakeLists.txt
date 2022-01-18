CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG 5985f0a7d2a725f6e843e8bc1a01e052a31d8e0b
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_fmt
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE fmt)
