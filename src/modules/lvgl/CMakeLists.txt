forte_add_io(LVGL "Integrating and Interacting with LVGL Widgets")

if (FORTE_IO_LVGL)
    set(FORTE_IO ON CACHE BOOL "Enable IO Modules" FORCE)

    forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    forte_add_sourcefile_hcpp(
            LVGLDeviceController
    )
    forte_add_sourcefile_hcpp(
            driver/LVGLBaseDriver
            driver/SDL2Driver
    )
    forte_add_sourcefile_hcpp(
            connector/LVGLConnectorInterface
            connector/LVGLAutoUIConnector
            connector/LVGLExternalConnector
    )
    forte_add_sourcefile_hcpp(
            handles/LVGLSubjectHandle
            handles/LVGLWidgetStateHandle
            handles/LVGLDropdownSelectedIndexHandle
            handles/LVGLLEDBrightnessHandle
            handles/LVGLNumberTextHandle
            handles/LVGLSliderValueHandle
            handles/LVGLSpinboxValueHandle
            handles/LVGLBarValueHandle
            handles/LVGLChartSeriesHandle
    )
    forte_add_sourcefile_hcpp(
            types/FORTE_LVGLBusAdapter
            types/FORTE_LVGLMaster
            types/FORTE_LVGLLED
            types/FORTE_LVGLButton
            types/FORTE_LVGLChart
            types/FORTE_LVGLCheckbox
            types/FORTE_LVGLDropdown
            types/FORTE_LVGLNumber
            types/FORTE_LVGLObserver
            types/FORTE_LVGLProgressbar
            types/FORTE_LVGLSlider
            types/FORTE_LVGLSpinbox
            types/FORTE_LVGLSubject
            types/FORTE_LVGLSwitch
    )

    forte_add_sourcefile_hcpp(fbs/ConveyorSim_fbt)

    forte_add_startup_hook(lvglStartupHook)
    forte_add_sourcefile_hcpp(startup)

    find_package(SDL2 REQUIRED)
    message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")

    add_compile_options(-march=native)

    set(LV_BUILD_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h")
    add_subdirectory(lvgl)
    target_include_directories(lvgl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
    target_link_libraries(lvgl PRIVATE ${SDL2_LIBRARIES})
    forte_add_link_library(lvgl)

    # Custom UI
    forte_add_subdirectory(lvgl_editor_ui)
    target_link_libraries(lib-ui PUBLIC lvgl)
    forte_add_link_library(lib-ui)
    target_include_directories(lib-ui PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/lvgl_editor_ui
    )
endif (FORTE_IO_LVGL)


# -DCMAKE_BUILD_TYPE=Debug