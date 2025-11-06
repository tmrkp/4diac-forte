# 4diac LVGL Module

## Usage

Exported FBs for 4diac IDE are in `fbs-xmi-spec/`

Main Function Hook must be added to `src/arch/main.cpp`:

```cpp
extern void lvglMainFunctionHook(); // <-- add this

int main(int argc, char *arg[]) {
   // [...]
   DEVLOG_INFO("FORTE is up and running\n");

  lvglMainFunctionHook(); // <-- add this
}
```

### Usage with Dynamic UI:

1. Enable class `LVGLAutoUIConnector`. Set `using LVGLConnector = LVGLAutoUIConnector;` in `LVGLDeviceController.h`
2. Disable any custom UI in `drivers/SDL2Driver.cpp`. Usually by removing `initUI()` call from `SDL2Driver::init()`.

### Usage with Static UI:

1. Enable class `LVGLExternalConnector`. Set `using LVGLConnector = LVGLExternalConnector;` in `LVGLDeviceController.h`
2. Implement UI in LVGL Editor in Folder `lvgl_editor_ui/`
3. Enable custom UI in `drivers/SDL2Driver.cpp`. Make sure `initUI()` is called in `SDL2Driver::init()`.
4. Check that a screen is loaded in `SDL2Driver::initUI()`. For example:
    ```
    void SDL2Driver::initUI() {
        lvgl_editor_ui_init(nullptr);
        lv_obj_t *main = demo1_create();
        lv_screen_load(main);
    }
    ```
   Replace `demo1` with any screen from `lvgl_editor_ui/screens/`. Make sure the screen's header files are included, for
   example: `#include "lvgl_editor_ui/screens/demo1_gen.h"`

## CMake Options:

Example compile options for macOS:

```
-DFORTE_ARCHITECTURE=MacOs
-DFORTE_LOGLEVEL=LOGDEBUG
-DFORTE_COM_ETH=ON
-DFORTE_COM_LOCAL=ON
-DFORTE_TESTS=OFF
-DFORTE_MODULE_CONVERT=ON
-DFORTE_MODULE_IEC61131=ON
-DFORTE_MODULE_UTILS=ON
-DFORTE_MODULE_MATH=ON
-DFORTE_LINKED_STRINGDICT=OFF
-DFORTE_IO=ON
-DFORTE_IO_LVGL=ON
-DCMAKE_BUILD_TYPE=Debug
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
-DLOGDEBUG=ON
-DCMAKE_CXX_FLAGS_DEBUG="-O0 -g"
-DCMAKE_C_FLAGS_DEBUG="-O0 -g"
-DCMAKE_OSX_ARCHITECTURES=arm64
```
