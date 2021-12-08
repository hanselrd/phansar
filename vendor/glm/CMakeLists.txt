CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm # master
    GIT_TAG 6ad79aae3eb5bf809c30bf1168171e9e55857e45
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_glm
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE glm)
