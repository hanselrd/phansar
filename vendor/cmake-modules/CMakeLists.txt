CPMAddPackage(
    NAME cmake-modules
    GITHUB_REPOSITORY rpavlik/cmake-modules # main
    GIT_TAG 77982ba193e2baeffae13876fd4b0b77cff5576c
    DOWNLOAD_ONLY YES)

if(cmake-modules_ADDED)
    set(_gitdescmoddir
        ${cmake-modules_SOURCE_DIR}
        CACHE INTERNAL "")
    include(${cmake-modules_SOURCE_DIR}/GetGitRevisionDescription.cmake)
endif()
