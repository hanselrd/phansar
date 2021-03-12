CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw # master
    GIT_TAG 4afa227a056681d2628894b0893527bf69496a41
    OPTIONS "GLFW_BUILD_DOCS OFF" "GLFW_INSTALL OFF")

# cmake-format: off
set(system_libs
    glfw)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_glfw
    ""
    ""
    "${system_libs}")
