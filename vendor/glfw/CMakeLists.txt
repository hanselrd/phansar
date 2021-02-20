CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw # master
    GIT_TAG 2c7f3ce91b4f22773855c43d6480824ed4ac9907
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
