CPMAddPackage(
    NAME json
    GITHUB_REPOSITORY ArthurSonzogni/nlohmann_json_cmake_fetchcontent # master
    GIT_TAG 391786c6c3abdd3eeb993a3154f1f2a4cfe137a0
    OPTIONS "JSON_BuildTests OFF" "JSON_ImplicitConversions OFF")

# cmake-format: off
set(system_libs
    nlohmann_json)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_json
    ""
    ""
    "${system_libs}")
