#pragma once

#include "LVGLBaseDriver.h"
#include "lvgl/lvgl.h"

class SDL2Driver : public LVGLBaseDriver {
  public:
    void init() override;

  private:
    lv_display_t *initHAL(int32_t w, int32_t h);
    void initUI();
};
