CPMAddPackage(
    NAME llvm-project
    GITHUB_REPOSITORY llvm/llvm-project # main
    GIT_TAG 1c10201d9660c1d6f43a7226ca7381bfa255105d
    DOWNLOAD_ONLY YES)
set(LLVM_ENABLE_PROJECTS
    "clang;clang-tools-extra;libcxx"
    CACHE STRING "" FORCE)
CPMAddPackage(
    NAME llvm-project-llvm
    SOURCE_DIR ${llvm-project_SOURCE_DIR}/llvm
    OPTIONS "CMAKE_POLICY_DEFAULT_CMP0116 OLD"
            "CMAKE_BUILD_TYPE Release"
            "LLVM_PARALLEL_LINK_JOBS 1"
            "LLVM_ENABLE_RTTI ON"
    EXCLUDE_FROM_ALL YES)

if(llvm-project-llvm_ADDED)
    include(${llvm-project-llvm_BINARY_DIR}/lib/cmake/llvm/LLVMConfig.cmake)
endif()

ph_add_library(
    NAME ph_vendor_llvm
    TYPE INTERFACE
    INCLUDE_DIRECTORIES
        INTERFACE
        ${llvm-project_SOURCE_DIR}/llvm/include
        ${llvm-project-llvm_BINARY_DIR}/include
        ${llvm-project_SOURCE_DIR}/clang/include
        ${llvm-project-llvm_BINARY_DIR}/tools/clang/include
    COMPILE_DEFINITIONS
        INTERFACE
        STDINC0="${llvm-project-llvm_BINARY_DIR}/include/c++/v1"
        STDINC1="${llvm-project-llvm_BINARY_DIR}/lib/clang/${LLVM_VERSION_MAJOR}.${LLVM_VERSION_MINOR}.${LLVM_VERSION_PATCH}/include"
    LINK_LIBRARIES
        INTERFACE
        clangASTMatchers
        clangBasic
        clangTooling
    DEPENDENCIES generate-cxx-headers)
