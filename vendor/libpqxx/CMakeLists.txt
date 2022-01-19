CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG c61cfe8cdc52970acef6abd138c9c201060bc230
    OPTIONS "SKIP_BUILD_TEST ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_libpqxx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pqxx)
