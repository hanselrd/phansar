CPMAddPackage(
  NAME cmake-modules
  GITHUB_REPOSITORY rpavlik/cmake-modules # main
  GIT_TAG 14094b5ed352d96e0a919237f3018f385f980344
  DOWNLOAD_ONLY YES)

if(cmake-modules_ADDED)
  set(_gitdescmoddir
      ${cmake-modules_SOURCE_DIR}
      CACHE INTERNAL "")
  include(${cmake-modules_SOURCE_DIR}/GetGitRevisionDescription.cmake)
endif()
