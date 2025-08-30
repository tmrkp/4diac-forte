#include "startup.h"

#include <queue>
#include <unistd.h>
#include "lvgl/lvgl.h"
#include "devlog.h"
#include "forte_sync.h"
#include "criticalregion.h"
#include "ui/ui.h"
#include "ui/screens/main_gen.h"

#include <iostream>

static CSyncObject mQueueMutex;
static std::queue<std::function<void()>> queue;

void runLater(std::function<void()> task) {
  CCriticalRegion criticalRegion(mQueueMutex);
  queue.push(std::move(task));
}

static void process() {
  std::queue<std::function<void()>> tasks;

  {
    CCriticalRegion criticalRegion(mQueueMutex);
    std::swap(tasks, queue);
  }

  while (!tasks.empty()) {
    tasks.front()();
    tasks.pop();
  }
}

static lv_display_t *hal_init(int32_t w, int32_t h) {
  lv_group_set_default(lv_group_create());

  lv_display_t *disp = lv_sdl_window_create(w, h);
  lv_sdl_window_set_title(disp, "LVGL");
  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);
  // LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  // lv_obj_t* cursor_obj;
  // cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  // lv_image_set_src(cursor_obj, &mouse_cursor_icon); /*Set the image source*/
  // lv_indev_set_cursor(mouse, cursor_obj); /*Connect the image  object to the driver*/
  // lv_indev_t* mousewheel = lv_sdl_mousewheel_create();
  // lv_indev_set_display(mousewheel, disp);
  // lv_indev_set_group(mousewheel, lv_group_get_default());

  lv_indev_t *kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());

  return disp;
}

void hmiStartupHook(int argc, char *arg[]) {
  lv_init();

  lv_log_register_print_cb([](lv_log_level_t level, const char *buf) {
    switch (level) {
      case LV_LOG_LEVEL_ERROR: DEVLOG_ERROR("[LVGL] %s", buf); break;
      case LV_LOG_LEVEL_WARN: DEVLOG_WARNING("[LVGL] %s", buf); break;
      default: DEVLOG_DEBUG("[LVGL] %s", buf); break;
    }
  });

  hal_init(640, 480);

  ui_init(nullptr);
  lv_obj_t *main = main_create();

  lv_obj_t *led = lv_led_create(lv_obj_find_by_name(main, "led_inject_1"));
  lv_obj_set_name(led, "lvled1");
  lv_led_off(led);

  led = lv_led_create(lv_obj_find_by_name(main, "led_inject_2"));
  lv_obj_set_name(led, "lvled2");
  lv_led_off(led);

  lv_obj_t *swtch = lv_switch_create(lv_obj_find_by_name(main, "switch_inject_1"));
  lv_obj_set_name(swtch, "lvswitch1");

  lv_screen_load(main);
}

void hmiMainFunctionHook() {
  while (1) {
    process();
    uint32_t delay = lv_timer_handler();
    usleep(delay * 1000);
  }
}
