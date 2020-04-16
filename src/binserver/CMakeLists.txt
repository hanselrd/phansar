# cmake-format: off
set(sources
    main.cpp)

set(libs
    ph_common
    ph_vendor_docopt
    ph_vendor_fmt)
# cmake-format: on

ph_add_generic_executable(ph_server "${sources}" "${libs}" "")
