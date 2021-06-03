CPMAddPackage(
    NAME trompeloeil
    GITHUB_REPOSITORY rollbear/trompeloeil # master
    GIT_TAG 85567d1e01694e16a21fd29114522a6de1458f36
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_trompeloeil
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE trompeloeil)
