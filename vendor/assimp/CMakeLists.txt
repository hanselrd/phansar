CPMAddPackage(
    NAME assimp
    GITHUB_REPOSITORY assimp/assimp # master
    GIT_TAG cd42b9954b8b92e5a35b9221eeb3f85937f119f7
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
