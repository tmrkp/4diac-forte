forte_add_io(HMI "Human Machine Interface")

if (FORTE_IO_HMI)
    set(FORTE_IO ON CACHE BOOL "Enable IO Modules" FORCE)
    message("Set FORTE_IO")

    define_property(DIRECTORY PROPERTY HMI_AUTOGENERATE)

    forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    forte_add_sourcefile_hcpp(
            HMIHandle
            HMIGenerator
            HMIDeviceController)
    forte_add_sourcefile_hcpp(
            types/FORTE_HMIBusAdapter
            types/FORTE_HMIMaster
            types/boolean_indicator/FORTE_HMIBooleanIndicator
            types/boolean_indicator/HMIBooleanIndicatorHandle
            types/button/FORTE_HMIButton
            types/button/HMIButtonHandle
            types/check_box/FORTE_HMICheckBox
            types/check_box/HMICheckBoxHandle
            types/drop_down/FORTE_HMIDropDown
            types/drop_down/HMIDropDownHandle
            types/number/FORTE_HMINumber
            types/number/HMINumberHandle
            types/progress_bar/FORTE_HMIProgressBar
            types/progress_bar/HMIProgressBarHandle
            types/slider/FORTE_HMISlider
            types/slider/HMISliderHandle
            types/subject/FORTE_HMISubject
            types/subject/HMISubjectHandle
            types/switch/FORTE_HMISwitch
            types/switch/HMISwitchHandle
    )

    forte_add_startup_hook(hmiStartupHook)
    forte_add_sourcefile_hcpp(startup)

    forte_add_subdirectory(ui)

    find_package(SDL2 REQUIRED)
    message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")

    add_compile_options(-march=native)

    set(LV_BUILD_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h")
    add_subdirectory(lvgl)
    target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
    target_link_libraries(lvgl PRIVATE ${SDL2_LIBRARIES})
    forte_add_link_library(lvgl)

endif (FORTE_IO_HMI)


# -DCMAKE_BUILD_TYPE=Debug