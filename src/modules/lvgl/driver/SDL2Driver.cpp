#include "SDL2Driver.h"

#include <unistd.h>
#include "devlog.h"

#include "ui/ui.h"
#include "ui/screens/main_gen.h"

void SDL2Driver::init() {
  lv_init();

  lv_log_register_print_cb([](lv_log_level_t level, const char *buf) {
    switch (level) {
      case LV_LOG_LEVEL_ERROR: DEVLOG_ERROR("[LVGL] %s", buf); break;
      case LV_LOG_LEVEL_WARN: DEVLOG_WARNING("[LVGL] %s", buf); break;
      default: DEVLOG_DEBUG("[LVGL] %s", buf); break;
    }
  });

  initHAL(640, 480);
  // initUI();
}

void SDL2Driver::runLoop() {
  while (true) {
    std::queue<std::function<void()>> tasks;

    {
      CCriticalRegion criticalRegion(taskQueueMutex);
      std::swap(tasks, taskQueue);
    }

    while (!tasks.empty()) {
      tasks.front()();
      tasks.pop();
    }

    uint32_t delay;
    {
      CCriticalRegion criticalRegion(timerMutex);
      delay = lv_timer_handler();
    }
    usleep(delay * 1000);
  }
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
  ui_init(nullptr);
  lv_obj_t *main = main_create();
  lv_obj_t *led = lv_led_create(lv_obj_find_by_name(main, "led_inject_1"));
  lv_obj_set_name(led, "lvled1");
  lv_led_off(led);
  lv_obj_t *swtch = lv_switch_create(lv_obj_find_by_name(main, "switch_inject_1"));
  lv_obj_set_name(swtch, "lvswitch1");

  lv_screen_load(main);
}
