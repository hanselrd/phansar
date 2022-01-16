CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG a03b88e0eb679ca0fbb79d9c54293e772b4f4a93
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_entt
    TYPE INTERFACE
    INCLUDE_DIRECTORIES SYSTEM INTERFACE ${entt_SOURCE_DIR}/single_include)
