CPMAddPackage(
  NAME bgfx
  GITHUB_REPOSITORY bkaradzic/bgfx.cmake # master
  GIT_TAG 03ae29e5bd90cd8cd54b2c659804047755090ebe
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_bgfx
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE bgfx)
