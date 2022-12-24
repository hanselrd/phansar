CPMAddPackage(
  NAME trompeloeil
  GITHUB_REPOSITORY rollbear/trompeloeil # main
  GIT_TAG 45772aefc1929d389b204a77562afd45661c0d35
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_trompeloeil
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE trompeloeil)
