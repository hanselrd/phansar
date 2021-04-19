CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # master
    GIT_TAG 0e925c71f32ed5c0e9174f901014f8c54b7bc336
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_trompeloeil
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE trompeloeil)
