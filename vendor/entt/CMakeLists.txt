CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 0ec763131043647d4c64fb1f6274da12c898b0ca
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_entt
    TYPE INTERFACE
    INCLUDE_DIRECTORIES SYSTEM INTERFACE ${entt_SOURCE_DIR}/single_include)
