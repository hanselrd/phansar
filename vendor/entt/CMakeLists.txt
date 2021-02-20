CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 18832fcb3765e02e66b033a0cf723683762463c0
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
