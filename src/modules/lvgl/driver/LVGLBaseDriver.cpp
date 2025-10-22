#include "LVGLBaseDriver.h"

#include <unistd.h>
#include "devlog.h"
#include "lvgl/lvgl.h"

CSyncObject LVGLBaseDriver::timerMutex;

void LVGLBaseDriver::init() {
  lv_init();

  lv_log_register_print_cb([](lv_log_level_t level, const char *buf) {
    switch (level) {
      case LV_LOG_LEVEL_ERROR: DEVLOG_ERROR("[LVGL] %s", buf); break;
      case LV_LOG_LEVEL_WARN: DEVLOG_WARNING("[LVGL] %s", buf); break;
      default: DEVLOG_DEBUG("[LVGL] %s", buf); break;
    }
  });
}

void LVGLBaseDriver::runLoop() {
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

void LVGLBaseDriver::runLater(std::function<void()> task) {
  CCriticalRegion criticalRegion(taskQueueMutex);
  taskQueue.push(std::move(task));
}
