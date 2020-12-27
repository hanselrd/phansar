include(GetGitRevisionDescription)

get_git_head_revision(GIT_REFSPEC GIT_HASH)
git_local_changes(GIT_CHANGES)

string(TIMESTAMP BUILD_TIMESTAMP UTC)
string(REPLACE "refs/heads/" "" GIT_BRANCH ${GIT_REFSPEC})
string(SUBSTRING ${GIT_HASH} 0 12 GIT_SHORT_HASH)
string(TOLOWER ${GIT_CHANGES} GIT_CHANGES)

configure_file(${CMAKE_SOURCE_DIR}/src/common/version.cpp.in ${CMAKE_BINARY_DIR}/version.cpp @ONLY)
