CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG a7aecbfcaa0e1586da9cf8175bd8d1c4383acd8c
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_fmt
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE fmt)
