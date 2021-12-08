CPMAddPackage(
    NAME cmake-modules
    GITHUB_REPOSITORY rpavlik/cmake-modules # main
    GIT_TAG f515c2fd2ed48641ac5ca0b11ccdce0c6246f874
    DOWNLOAD_ONLY YES)

if(cmake-modules_ADDED)
    set(_gitdescmoddir
        ${cmake-modules_SOURCE_DIR}
        CACHE INTERNAL "")
    include(${cmake-modules_SOURCE_DIR}/GetGitRevisionDescription.cmake)
endif()
