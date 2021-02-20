CPMAddPackage(
    NAME cmake-modules
    GITHUB_REPOSITORY rpavlik/cmake-modules # main
    GIT_TAG 6a748896188fdf3f885820ccd686393ea5215dbf
    DOWNLOAD_ONLY YES)

if(cmake-modules_ADDED)
    set(_gitdescmoddir
        ${cmake-modules_SOURCE_DIR}
        CACHE INTERNAL "")
    include(${cmake-modules_SOURCE_DIR}/GetGitRevisionDescription.cmake)
endif()
