#include <iostream>
#include <unistd.h>
#include "lvgl/lvgl.h"

static lv_obj_t *led;
static bool was_pressed;

static std::mutex mutex;
static std::queue<std::function<void()>> queue;

void runLater(std::function<void()> task) {
  std::lock_guard<std::mutex> lock(mutex);
  queue.push(std::move(task));
}

static void process() {
  std::queue<std::function<void()>> tasks;

  {
    std::lock_guard<std::mutex> lock(mutex);
    std::swap(tasks, queue);
  }

  while (!tasks.empty()) {
    tasks.front()();
    tasks.pop();
  }
}

void hmi_set_led(bool on) {
  runLater([on]() {
    if (on) {
      lv_led_on(led);
    } else {
      lv_led_off(led);
    }
  });
}

bool hmi_button_was_pressed() {
  if (was_pressed) {
    was_pressed = false;
    return true;
  }
  return false;
}

static lv_display_t *hal_init(int32_t w, int32_t h) {
  lv_group_set_default(lv_group_create());

  lv_display_t *disp = lv_sdl_window_create(w, h);
  lv_sdl_window_set_title(disp, "LVGL Test");
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

static void create_demo() {
  lv_obj_t *layout = lv_obj_create(lv_screen_active());
  lv_obj_set_size(layout, lv_pct(100), lv_pct(100));
  lv_obj_set_flex_flow(layout, LV_FLEX_FLOW_COLUMN);

  static lv_obj_t *btn = lv_button_create(layout);
  static lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, "Toggle");

  lv_obj_add_event_cb(
      btn,
      [](lv_event_t *event) {
        std::cout << "Button was clicked" << std::endl;
        was_pressed = true;
      },
      LV_EVENT_CLICKED, nullptr);

  led = lv_led_create(layout);
  lv_led_off(led);
}

void hmiStartupHook(int argc, char *arg[]) {
  lv_init();

  lv_log_register_print_cb([](lv_log_level_t level, const char *buf) { std::cout << buf << std::endl; });

  hal_init(480, 320);
  create_demo();
}

void hmiMainFunctionHook() {
  while (1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    process();
    lv_timer_handler();
    usleep(1000);
  }
}
