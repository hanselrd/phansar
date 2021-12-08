CPMAddPackage(
    NAME json
    GITHUB_REPOSITORY ArthurSonzogni/nlohmann_json_cmake_fetchcontent # master
    GIT_TAG b48095ee99aff048dc4760dd644b848bc1e6f0c3
    OPTIONS "JSON_BuildTests OFF" "JSON_ImplicitConversions OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_json
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE nlohmann_json)
