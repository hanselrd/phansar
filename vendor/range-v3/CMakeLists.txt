CPMAddPackage(
  NAME range-v3
  GITHUB_REPOSITORY ericniebler/range-v3 # master
  GIT_TAG 4624c63972c6f2c2871c7b87813c42048ddb80ad
  EXCLUDE_FROM_ALL YES)

ph_add_library(
  NAME ph_vendor_rangev3
  TYPE INTERFACE
  LINK_LIBRARIES SYSTEM INTERFACE range-v3)
