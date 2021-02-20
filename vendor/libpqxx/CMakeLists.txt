CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG aecbc5e0e033b2817b8d7f58695c6f79ec8aee04
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
