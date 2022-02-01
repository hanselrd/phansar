CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG a34a97cc1d7d50ed6b05bd315ecef7aeb97f1364
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_fmt
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE fmt)
