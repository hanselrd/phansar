CPMAddPackage(
    NAME SDL_mixer
    GITHUB_REPOSITORY libsdl-org/SDL_mixer # master
    GIT_TAG 9e4993474f8b435f50714dac7c5827b5962277df
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_sdl2_mixer
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE SDL2_mixer)
