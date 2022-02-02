CPMAddPackage(
    NAME lua
    GITHUB_REPOSITORY lua/lua # master
    GIT_TAG 5d708c3f9cae12820e415d4f89c9eacbe2ab964b
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_lua
    TYPE STATIC
    INCLUDE_DIRECTORIES PUBLIC ${lua_SOURCE_DIR}
    COMPILE_DEFINITIONS PRIVATE MAKE_LIB
    COMPILE_FEATURES PRIVATE ${default_compile_features}
    SOURCES PRIVATE ${lua_SOURCE_DIR}/onelua.c)
