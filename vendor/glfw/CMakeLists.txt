CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw # master
    GIT_TAG 33cd8b865d9289cfbcf3d95e6e68e4050b94fcd3
    OPTIONS "GLFW_BUILD_DOCS OFF" "GLFW_INSTALL OFF"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_glfw
    TYPE INTERFACE
    LINK_LIBRARIES INTERFACE glfw)
