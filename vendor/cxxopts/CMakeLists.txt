CPMAddPackage(
  NAME cxxopts
  GITHUB_REPOSITORY jarro2783/cxxopts # master
  GIT_TAG 32afbc65263e42fa089f473d5a6131983d9b7200
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_cxxopts
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE cxxopts)
