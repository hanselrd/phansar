CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm # master
    GIT_TAG 0.9.9.8)

# cmake-format: off
set(system_libs
    glm)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_glm
    ""
    ""
    "${system_libs}")
