CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # main
    GIT_TAG 31e72dc98508cf290db8ebbf4c9a7984a18518a9
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_trompeloeil
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE trompeloeil)
