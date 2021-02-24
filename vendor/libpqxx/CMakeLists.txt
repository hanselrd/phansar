CPMAddPackage(
    NAME libpqxx
    GITHUB_REPOSITORY jtv/libpqxx # master
    GIT_TAG cbd2b35ef5bce8a1fc8bfd1efd804d965976ce23
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
