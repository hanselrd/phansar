function(set_project_warnings project_name)
    option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

    set(MSVC_WARNINGS
        /W4
        /w14242
        /w14254
        /w14263
        /w14265
        /w14287
        /w14296
        /w14311
        /w14545
        /w14546
        /w14547
        /w14549
        /w14555
        /w14619
        /w14640
        /w14826
        /w14905
        /w14906
        /w14928
        /we4289)

    set(CLANG_WARNINGS
        -Wall
        -Wcast-align # ???
        -Wconversion
        -Wdouble-promotion
        -Wextra
        -Wformat=2
        -Wnon-virtual-dtor # ???
        -Wnull-dereference # ???
        -Wold-style-cast # ???
        -Woverloaded-virtual # ???
        -Wpedantic
        -Wshadow
        -Wsign-conversion # ???
        -Wundef
        -Wunused
        -fno-common)

    if(WARNINGS_AS_ERRORS)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
    endif()

    set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wduplicated-branches # ???
        -Wduplicated-cond # ???
        -Wformat-overflow=2
        -Wformat-truncation=2
        -Wlogical-op # ???
        -Wmisleading-indentation # ???
        -Wuseless-cast # ???
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(PROJECT_WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    endif()

    target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
endfunction()
