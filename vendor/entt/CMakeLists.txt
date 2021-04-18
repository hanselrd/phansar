CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 5d15a3d69f433a0e3fce266caaeb87c77c10453c
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_entt
    TYPE INTERFACE
    INCLUDE_DIRECTORIES INTERFACE ${entt_SOURCE_DIR}/single_include)
