CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 38ab02ff8837c269ecffd54165d8fe4f5f918be1
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
