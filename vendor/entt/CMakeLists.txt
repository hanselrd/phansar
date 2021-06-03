CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 0b3e3fd19adbb8b56b92908493559a7eda7ce644
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_entt
    TYPE INTERFACE
    INCLUDE_DIRECTORIES SYSTEM INTERFACE ${entt_SOURCE_DIR}/single_include)
