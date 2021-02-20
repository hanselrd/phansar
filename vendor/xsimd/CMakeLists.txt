CPMAddPackage(
    NAME xsimd
    GITHUB_REPOSITORY xtensor-stack/xsimd # master
    GIT_TAG 634ff89eaab1f129138da745b95219e47c70b289)

# cmake-format: off
set(system_libs
    xsimd)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_xsimd
    ""
    ""
    "${system_libs}")
