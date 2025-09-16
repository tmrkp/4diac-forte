#pragma once

#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

using namespace forte::core::io;

class LVGLSliderValueHandle : public IOHandle {
  public:
    LVGLSliderValueHandle(IODeviceController *paController,
                         IOMapper::Direction paDirection,
                         CIEC_ANY::EDataTypeID paType,
                         lv_obj_t *paWidget,
                         lv_event_code_t paEventCode);

    ~LVGLSliderValueHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    static void changeHandler(lv_event_t *e);

    lv_obj_t *mWidget;
};
