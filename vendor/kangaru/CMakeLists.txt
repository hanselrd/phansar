CPMAddPackage(
    NAME kangaru
    GITHUB_REPOSITORY gracicot/kangaru # master
    GIT_TAG 4852a2e6ded718fefc3cc94c32eaa6e54692e332
    OPTIONS "KANGARU_INSTALL OFF" "KANGARU_EXPORT OFF" "KANGARU_REVERSE_DESTRUCTION ON")

# cmake-format: off
set(system_libs
    kangaru)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_kangaru
    ""
    ""
    "${system_libs}")
