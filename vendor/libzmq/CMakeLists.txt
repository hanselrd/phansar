CPMAddPackage(
  NAME libzmq
  GITHUB_REPOSITORY zeromq/libzmq # master
  GIT_TAG bdd471fa17100fe84f64da348951dab3ee4780bb
  OPTIONS "BUILD_SHARED OFF"
          "BUILD_STATIC ON"
          "BUILD_TESTS OFF"
          "WITH_DOC OFF"
          "WITH_DOCS OFF"
          "WITH_LIBSODIUM OFF"
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_libzmq
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE libzmq-static)
