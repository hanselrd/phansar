CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG c0b7e682b629241fc53d037920fb33dfa4ed873d
    OPTIONS "SKIP_BUILD_TEST ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_libpqxx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pqxx)
