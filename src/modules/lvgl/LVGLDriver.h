#pragma once

#include <functional>
#include <queue>
#include "criticalregion.h"
#include "lvgl/lvgl.h"

class LVGLDriver {
  public:
    static void init();
    static void main();
    static void stop();

    static void runLater(std::function<void()> task);

    static CSyncObject timerMutex;

  private:
    static std::atomic<bool> running;

    static CSyncObject taskQueueMutex;
    static std::queue<std::function<void()>> taskQueue;

    static lv_display_t *initHAL(int32_t w, int32_t h);
    static void initUI();
};
