CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG 53452084ea97514cb4866932ff798108162f78d4
    OPTIONS "SKIP_BUILD_TEST ON")

# cmake-format: off
set(system_libs
    pqxx)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_libpqxx
    ""
    ""
    "${system_libs}")
