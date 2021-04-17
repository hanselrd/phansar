CPMAddPackage(
    NAME llvm-project
    GITHUB_REPOSITORY llvm/llvm-project # main
    GIT_TAG 4457565757ea91207b7e5f2ce7b7bf173bfd2c0c
    DOWNLOAD_ONLY YES)
set(LLVM_ENABLE_PROJECTS
    "clang;clang-tools-extra"
    CACHE STRING "" FORCE)
CPMAddPackage(
    NAME llvm-project-llvm
    SOURCE_DIR ${llvm-project_SOURCE_DIR}/llvm
    OPTIONS "CMAKE_POLICY_DEFAULT_CMP0116 OLD"
            "CMAKE_BUILD_TYPE Release"
            "LLVM_PARALLEL_LINK_JOBS 1"
            "LLVM_ENABLE_RTTI ON"
    EXCLUDE_FROM_ALL YES)

# cmake-format: off
set(includes
    ${llvm-project_SOURCE_DIR}/llvm/include
    ${llvm-project-llvm_BINARY_DIR}/include
    ${llvm-project_SOURCE_DIR}/clang/include
    ${llvm-project-llvm_BINARY_DIR}/tools/clang/include)

set(system_libs
    clangASTMatchers
    clangBasic
    clangTooling)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_llvm
    "${includes}"
    ""
    "${system_libs}")
