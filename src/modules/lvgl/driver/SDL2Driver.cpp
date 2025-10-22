#include "SDL2Driver.h"

#include "lvgl_editor_ui/lvgl_editor_ui.h"
#include "lvgl_editor_ui/screens/demo1_gen.h"

void SDL2Driver::init() {
  LVGLBaseDriver::init();

  initHAL(640, 480);
  initUI();
}

lv_display_t *SDL2Driver::initHAL(int32_t w, int32_t h) {
  lv_group_set_default(lv_group_create());

  lv_display_t *disp = lv_sdl_window_create(w, h);
  lv_sdl_window_set_title(disp, "LVGL");
  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  lv_indev_t *kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());

  return disp;
}

void SDL2Driver::initUI() {
  lvgl_editor_ui_init(nullptr);
  lv_obj_t *main = demo1_create();
  lv_screen_load(main);
}
