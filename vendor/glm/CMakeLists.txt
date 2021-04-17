CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm # master
    GIT_TAG 761a842a595f58acfc01cc5c7760ff351feaaece
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(system_libs
    glm)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_glm
    ""
    ""
    "${system_libs}")
