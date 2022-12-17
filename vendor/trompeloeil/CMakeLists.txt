CPMAddPackage(
  NAME trompeloeil
  GITHUB_REPOSITORY rollbear/trompeloeil # main
  GIT_TAG dd2c8d7fe62ec735fd892150382c467c816aa0ca
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_trompeloeil
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE trompeloeil)
