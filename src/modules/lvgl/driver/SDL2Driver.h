#pragma once

#include "LVGLDriverInterface.h"
#include "lvgl/lvgl.h"

class SDL2Driver : public LVGLDriverInterface {
  public:
    void init() override;
    void runLoop() override;

     lv_display_t *initHAL(int32_t w, int32_t h);
     void initUI();
};
