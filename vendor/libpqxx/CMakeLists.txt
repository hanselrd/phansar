CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG 22d49918590e8c7a9fe92cfe546de8178a34403f
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
