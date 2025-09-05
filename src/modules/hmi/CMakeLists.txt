forte_add_io(HMI "Human Machine Interface")

if (FORTE_IO_HMI)
    set(FORTE_IO ON CACHE BOOL "Enable IO Modules" FORCE)

    forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    forte_add_sourcefile_hcpp(
            handles/HMISubjectHandle
            handles/HMIWidgetStateHandle
            handles/HMIDropdownSelectedIndexHandle
            handles/HMILEDBrightnessHandle
            handles/HMILabelTextHandle
    )
    forte_add_sourcefile_hcpp(
            HMIGenerator
            HMIDeviceController
            HMIDriver)
    forte_add_sourcefile_hcpp(
            types/FORTE_HMIBusAdapter
            types/FORTE_HMIMaster
            types/FORTE_HMILED
            types/FORTE_HMIButton
            types/FORTE_HMICheckBox
            types/FORTE_HMIDropDown
            types/FORTE_HMINumber
            types/FORTE_HMIObserver
            types/FORTE_HMIProgressBar
            types/FORTE_HMISlider
            types/FORTE_HMISpinBox
            types/FORTE_HMISubject
            types/FORTE_HMISwitch
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