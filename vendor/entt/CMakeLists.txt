CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY skypjack/entt # master
    GIT_TAG 9d72ffb9fe0ce4a15bab3729b52fcb0adace4d7f
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
