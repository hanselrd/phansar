CPMAddPackage(
    NAME SDL_mixer
    GITHUB_REPOSITORY libsdl-org/SDL_mixer # master
    GIT_TAG 6845d9f3cb3f35542f1ec7e74dba6b30bf968959
    OPTIONS "BUILD_SHARED_LIBS ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_sdl2_mixer
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE SDL2_mixer)
