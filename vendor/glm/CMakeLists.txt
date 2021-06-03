CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm # master
    GIT_TAG 66062497b104ca7c297321bd0e970869b1e6ece5
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_glm
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE glm)
