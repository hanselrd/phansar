CPMAddPackage(
  NAME cppcodec
  GITHUB_REPOSITORY tplgy/cppcodec # master
  GIT_TAG 8019b8b580f8573c33c50372baec7039dfe5a8ce
  DOWNLOAD_ONLY YES)

ph_add_library(
  NAME ph_vendor_cppcodec
  TYPE INTERFACE
  INCLUDE_DIRECTORIES SYSTEM INTERFACE ${cppcodec_SOURCE_DIR})
