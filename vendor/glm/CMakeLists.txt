CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm # master
    GIT_TAG fc8f4bb442b9540969f2f3f351c4960d91bca17a
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_glm
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE glm)
