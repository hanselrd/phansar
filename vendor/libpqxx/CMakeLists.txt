CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG 514d301aee01c87b26d9787452ef1d28693d69c6
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
