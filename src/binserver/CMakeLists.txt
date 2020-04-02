set(sources
    main.cpp)

set(libs
    ph_common)

ph_add_generic_executable(ph_server "${sources}" "${libs}" "")
