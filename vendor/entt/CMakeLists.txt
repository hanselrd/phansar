CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG c876350e05c1879fe0b2dfabdcf81e94313175b2
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
