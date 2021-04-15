CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 5d15a3d69f433a0e3fce266caaeb87c77c10453c
    DOWNLOAD_ONLY YES)

# cmake-format: off
set(includes
    ${entt_SOURCE_DIR}/single_include)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_entt
    "${includes}"
    ""
    "")
