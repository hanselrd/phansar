CPMAddPackage(
  NAME capnproto
  GITHUB_REPOSITORY capnproto/capnproto # master
  GIT_TAG 3927c10da22bab71c6a2ed87ecc2f6ac6aecf041
  OPTIONS "BUILD_TESTING OFF" "CMAKE_CXX_EXTENSIONS ON" "CMAKE_C_EXTENSIONS ON"
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_capnproto
  TYPE INTERFACE
  LINK_LIBRARIES
    SYSTEM
    INTERFACE
    capnp
    capnp-json)
