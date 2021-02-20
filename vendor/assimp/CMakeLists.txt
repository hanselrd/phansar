CPMAddPackage(
    NAME assimp
    GITHUB_REPOSITORY assimp/assimp # master
    GIT_TAG 26ebeaea5cb92f841fc5e2da9da379718223e831
    OPTIONS "BUILD_SHARED_LIBS OFF"
            "ASSIMP_BUILD_ZLIB OFF"
            "ASSIMP_BUILD_ASSIMP_TOOLS OFF"
            "ASSIMP_BUILD_TESTS OFF"
            "ASSIMP_INSTALL OFF"
            "ASSIMP_INJECT_DEBUG_POSTFIX OFF"
            "ASSIMP_IGNORE_GIT_HASH OFF")

# cmake-format: off
set(system_libs
    assimp)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_assimp
    ""
    ""
    "${system_libs}")
