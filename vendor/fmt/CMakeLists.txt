CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt # master
    GIT_TAG c5d4fcb1195afe57c1fe358de1c7a2e636d66bf6
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_fmt
    TYPE INTERFACE
    LINK_LIBRARIES INTERFACE fmt)
