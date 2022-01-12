CPMAddPackage(
    NAME json
    GITHUB_REPOSITORY ArthurSonzogni/nlohmann_json_cmake_fetchcontent # master
    GIT_TAG 6aebf09233951e4ce30a63919186a70b2b195756
    OPTIONS "JSON_BuildTests OFF" "JSON_ImplicitConversions OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_json
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE nlohmann_json)
