CPMAddPackage(
  NAME xsimd
  GITHUB_REPOSITORY xtensor-stack/xsimd # master
  GIT_TAG 96a24aecd6f76b3f90dd3b8469a68da1f28a27a5
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_xsimd
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE xsimd)
