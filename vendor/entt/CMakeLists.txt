CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 3328c7e78bcf638a78d7a601d3780a10e7dd712c
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_entt
    TYPE INTERFACE
    INCLUDE_DIRECTORIES SYSTEM INTERFACE ${entt_SOURCE_DIR}/single_include)
