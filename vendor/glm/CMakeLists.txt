CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm # master
    GIT_TAG 761a842a595f58acfc01cc5c7760ff351feaaece
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_glm
    TYPE INTERFACE
    LINK_LIBRARIES INTERFACE glm)
