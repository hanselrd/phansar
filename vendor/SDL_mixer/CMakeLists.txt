CPMAddPackage(
    NAME SDL_mixer
    GITHUB_REPOSITORY libsdl-org/SDL_mixer # master
    GIT_TAG 8df5ea8f1a1ee39d395f37d0e7b48487f3420458
    OPTIONS "BUILD_SHARED_LIBS ON"
    EXCLUDE_FROM_ALL YES)

ph_add_library(
    NAME ph_vendor_sdl2_mixer
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE SDL2_mixer)
