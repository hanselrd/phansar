CPMAddPackage(
    NAME SDL_ttf
    GITHUB_REPOSITORY libsdl-org/SDL_ttf # main
    GIT_TAG 3a0dd6d0880254956275569b1144bdde16a98e47
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_sdl2_ttf
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE SDL2_ttf)
