CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG 3d03270fa50dca402e5dae5fcf60eed52c025ff4
    OPTIONS "SKIP_BUILD_TEST ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_libpqxx
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE pqxx)
