CPMAddPackage(
    NAME cmake-modules
    GITHUB_REPOSITORY rpavlik/cmake-modules # main
    GIT_TAG 3933abd958596bc660d180a22e86991ac477b68b
    DOWNLOAD_ONLY YES)

if(cmake-modules_ADDED)
    set(_gitdescmoddir
        ${cmake-modules_SOURCE_DIR}
        CACHE INTERNAL "")
    include(${cmake-modules_SOURCE_DIR}/GetGitRevisionDescription.cmake)
endif()
