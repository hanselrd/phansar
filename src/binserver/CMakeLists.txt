set(sources
    main.cpp)

set(libs
    common)

ph_add_generic_executable(ph_server ${sources} ${libs})
