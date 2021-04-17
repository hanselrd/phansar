CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw # master
    GIT_TAG 33cd8b865d9289cfbcf3d95e6e68e4050b94fcd3
    OPTIONS "GLFW_BUILD_DOCS OFF" "GLFW_INSTALL OFF"
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(system_libs
    glfw)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_glfw
    ""
    ""
    "${system_libs}")
