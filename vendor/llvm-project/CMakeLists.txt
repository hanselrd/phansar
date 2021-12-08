CPMAddPackage(
    NAME llvm-project
    GITHUB_REPOSITORY llvm/llvm-project # main
    GIT_TAG e4800fc099ad204f88c432276e6488772042bffc
    DOWNLOAD_ONLY YES)
set(LLVM_ENABLE_PROJECTS
    "clang"
    CACHE STRING "" FORCE)
set(LLVM_ENABLE_RUNTIMES
    "libcxx;libcxxabi"
    CACHE STRING "" FORCE)
set(LLVM_TARGETS_TO_BUILD
    "X86"
    CACHE STRING "" FORCE)
CPMAddPackage(
    NAME llvm-project-llvm
    SOURCE_DIR ${llvm-project_SOURCE_DIR}/llvm
    OPTIONS "CMAKE_POLICY_DEFAULT_CMP0114 OLD"
            "CMAKE_POLICY_DEFAULT_CMP0116 OLD"
            "LLVM_BUILD_BENCHMARKS OFF"
            "LLVM_BUILD_DOCS OFF"
            "LLVM_BUILD_EXAMPLES OFF"
            "LLVM_BUILD_INSTRUMENTED_COVERAGE OFF"
            "LLVM_BUILD_TESTS OFF"
            "LLVM_BUILD_TOOLS OFF"
            "LLVM_ENABLE_ASSERTIONS OFF"
            "LLVM_ENABLE_EH ON"
            "LLVM_ENABLE_IDE OFF"
            "LLVM_ENABLE_RTTI ON"
            "LLVM_INCLUDE_BENCHMARKS OFF"
            "LLVM_INCLUDE_EXAMPLES OFF"
            "LLVM_INCLUDE_TESTS OFF"
            "LLVM_INCLUDE_TOOLS ON"
            "LLVM_PARALLEL_LINK_JOBS 1"
            "LLVM_OPTIMIZED_TABLEGEN ON"
            "LLVM_USE_SPLIT_DWARF ON"
            "CLANG_ENABLE_STATIC_ANALYZER OFF"
            "CLANG_ENABLE_ARCMT OFF"
    EXCLUDE_FROM_ALL YES)

if(llvm-project-llvm_ADDED)
    include(${llvm-project-llvm_BINARY_DIR}/lib/cmake/llvm/LLVMConfig.cmake)
endif()

ph_add_library(
    NAME ph_vendor_llvm
    TYPE INTERFACE
    INCLUDE_DIRECTORIES
        SYSTEM
        INTERFACE
        ${llvm-project_SOURCE_DIR}/llvm/include
        ${llvm-project-llvm_BINARY_DIR}/include
        ${llvm-project_SOURCE_DIR}/clang/include
        ${llvm-project-llvm_BINARY_DIR}/tools/clang/include
    COMPILE_DEFINITIONS
        INTERFACE
        STDINC0="${llvm-project-llvm_BINARY_DIR}/include/${LLVM_HOST_TRIPLE}/c++/v1"
        STDINC1="${llvm-project-llvm_BINARY_DIR}/include/c++/v1"
        STDINC2="${llvm-project-llvm_BINARY_DIR}/lib/clang/${LLVM_VERSION_MAJOR}.${LLVM_VERSION_MINOR}.${LLVM_VERSION_PATCH}/include"
        STDLIB0="${llvm-project-llvm_BINARY_DIR}/lib"
    LINK_LIBRARIES
        SYSTEM
        INTERFACE
        clangASTMatchers
        clangBasic
        clangTooling
    DEPENDENCIES runtimes)
