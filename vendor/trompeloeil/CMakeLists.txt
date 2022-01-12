CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # main
    GIT_TAG 6b2742870a4b08e87cf104e2e9e7904c3818275d
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_trompeloeil
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE trompeloeil)
