CPMAddPackage(
    NAME json
    GITHUB_REPOSITORY ArthurSonzogni/nlohmann_json_cmake_fetchcontent # master
    GIT_TAG 391786c6c3abdd3eeb993a3154f1f2a4cfe137a0
    OPTIONS "JSON_BuildTests OFF" "JSON_ImplicitConversions OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_json
    TYPE INTERFACE
    LINK_LIBRARIES INTERFACE nlohmann_json)
