CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm # master
    GIT_TAG 6347f62261da5be4e27a256e28aef6abc0ba884d)

# cmake-format: off
set(system_libs
    glm)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_glm
    ""
    ""
    "${system_libs}")
