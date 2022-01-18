CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG 55f40b426d66f90faaf7251f7bc66a7aa28612ca
    OPTIONS "SKIP_BUILD_TEST ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_libpqxx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pqxx)
