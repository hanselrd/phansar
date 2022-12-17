CPMAddPackage(
  NAME json
  GITHUB_REPOSITORY ArthurSonzogni/nlohmann_json_cmake_fetchcontent # master
  GIT_TAG 67e6070f9d9a44b4dec79ebe6b591f39d2285593
  OPTIONS "JSON_BuildTests OFF" "JSON_ImplicitConversions OFF"
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_json
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE nlohmann_json)
