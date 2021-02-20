CPMAddPackage(
    NAME docopt.cpp
    GITHUB_REPOSITORY docopt/docopt.cpp # master
    GIT_TAG 6f5de76970be94a6f1e4556d1716593100e285d2)

# cmake-format: off
set(system_libs
    docopt_s)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_docopt
    ""
    ""
    "${system_libs}")
