CPMAddPackage(
    NAME cppcodec
    GITHUB_REPOSITORY tplgy/cppcodec # master
    GIT_TAG bd6ddf95129e769b50ef63e0f558fa21364f3f65
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_cppcodec
    TYPE INTERFACE
    INCLUDE_DIRECTORIES INTERFACE ${cppcodec_SOURCE_DIR})
