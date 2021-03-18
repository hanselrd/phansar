CPMAddPackage(
    NAME assimp
    GITHUB_REPOSITORY assimp/assimp # master
    GIT_TAG 0dbaeb57e3b0127df90679ada52a738d8c1e329a
    OPTIONS "BUILD_SHARED_LIBS OFF"
            "ASSIMP_BUILD_ZLIB ON"
            "ASSIMP_BUILD_ASSIMP_TOOLS OFF"
            "ASSIMP_BUILD_TESTS OFF"
            "ASSIMP_INSTALL OFF"
            "ASSIMP_INJECT_DEBUG_POSTFIX OFF"
            "ASSIMP_IGNORE_GIT_HASH OFF"
            "ASSIMP_BUILD_DRACO OFF"
            "ASSIMP_NO_EXPORT ON"
            "ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF"
            "ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF"
            "ASSIMP_BUILD_FBX_IMPORTER ON"
            "ASSIMP_BUILD_OBJ_IMPORTER ON")

# cmake-format: off
set(system_libs
    assimp)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_assimp
    ""
    ""
    "${system_libs}")
