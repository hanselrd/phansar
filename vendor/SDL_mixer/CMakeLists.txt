CPMAddPackage(
    NAME SDL_mixer
    GITHUB_REPOSITORY libsdl-org/SDL_mixer # main
    GIT_TAG ffd05891bcaca5c42cfd70ce940af3cd8f44dfbf
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_sdl2_mixer
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE SDL2_mixer)
