CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2 # v2.x
    GIT_TAG 33794a204c00158b15eeda38bd2e30a5a57533fc
    OPTIONS "CATCH_BUILD_TESTING OFF" "CATCH_INSTALL_DOCS OFF" "CATCH_INSTALL_HELPERS OFF"
    EXCLUDE_FROM_ALL YES)

if(Catch2_ADDED)
    include(${Catch2_SOURCE_DIR}/contrib/Catch.cmake)
endif()

ph_add_library(
    NAME ph_vendor_catch2
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE Catch2)
