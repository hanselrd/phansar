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
            "BUILD_PACKAGE OFF"
    EXCLUDE_FROM_ALL YES)

if(rttr_ADDED)
    set_target_properties(rttr_core_lib PROPERTIES COMPILE_OPTIONS "")
endif()

ph_add_library(
    NAME ph_vendor_rttr
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE rttr_core_lib)
