CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG e094e37da5f8b75cc009b543f6849ceb78192910
    OPTIONS "SKIP_BUILD_TEST ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_libpqxx
    TYPE INTERFACE
    LINK_LIBRARIES INTERFACE pqxx)
