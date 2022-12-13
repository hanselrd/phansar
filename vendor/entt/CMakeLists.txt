CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 9d38f60207e825dd44e35c34e8bb42dfee489437
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_entt
    TYPE INTERFACE
    INCLUDE_DIRECTORIES SYSTEM INTERFACE ${entt_SOURCE_DIR}/single_include)
