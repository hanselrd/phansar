CPMAddPackage(
    NAME assimp
    GITHUB_REPOSITORY assimp/assimp # master
    GIT_TAG 6c4addf158df692642b637cb060f251f7b859764
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
            "ASSIMP_BUILD_OBJ_IMPORTER ON"
    EXCLUDE_FROM_ALL YES)

if(assimp_ADDED)
    target_compile_definitions(assimp PRIVATE _POSIX_C_SOURCE=2008009L)
endif()

ph_add_library(
    NAME ph_vendor_assimp
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE assimp)
