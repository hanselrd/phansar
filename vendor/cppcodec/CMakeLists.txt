CPMAddPackage(
    NAME cppcodec
    GITHUB_REPOSITORY tplgy/cppcodec # master
    GIT_TAG 9838f9eaf077e42121cb42361e9a1613901fc5e8
    DOWNLOAD_ONLY YES)

ph_add_library(
    NAME ph_vendor_cppcodec
    TYPE INTERFACE
    INCLUDE_DIRECTORIES SYSTEM INTERFACE ${cppcodec_SOURCE_DIR})
