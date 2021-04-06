CPMAddPackage(
    NAME rttr
    GITHUB_REPOSITORY rttrorg/rttr # master
    GIT_TAG b16fccf0fbbbf94064bf2a6c7c47f2b910ab31f1
    OPTIONS "BUILD_RTTR_DYNAMIC OFF"
            "BUILD_UNIT_TESTS OFF"
            "BUILD_STATIC ON"
            "BUILD_EXAMPLES OFF"
            "BUILD_DOCUMENTATION OFF"
            "BUILD_INSTALLER OFF"
            "BUILD_PACKAGE OFF")

if(rttr_ADDED)
    set_target_properties(rttr_core_lib PROPERTIES COMPILE_OPTIONS "")
endif()

# cmake-format: off
set(system_libs
    rttr_core_lib)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_rttr
    ""
    ""
    "${system_libs}")
