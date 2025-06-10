forte_add_io(HMI "Human Machine Interface")

if (FORTE_IO_HMI)
    set(FORTE_IO ON CACHE BOOL "Enable IO Modules" FORCE)
    message("Set FORTE_IO")

    forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    forte_add_sourcefile_hcpp(HMIHandle HMIDeviceController)
    forte_add_sourcefile_hcpp(types/HMIMaster types/HMIBusAdapter types/HMIButton)
    #    forte_add_sourcefile_hcpp(types/HMI_fbt)

    forte_add_startup_hook(hmiStartupHook)
    forte_add_sourcefile_cpp(startup.cpp)

    find_package(SDL2 REQUIRED)
    message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")

    # Remove ARM-specific compile and linker options
    #    add_compile_options(-march=native)

    set(LV_BUILD_CONF_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h")
    add_subdirectory(lvgl)
    target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
    target_link_libraries(lvgl PRIVATE ${SDL2_LIBRARIES})
    forte_add_link_library(lvgl)

endif (FORTE_IO_HMI)


# -DCMAKE_BUILD_TYPE=Debug