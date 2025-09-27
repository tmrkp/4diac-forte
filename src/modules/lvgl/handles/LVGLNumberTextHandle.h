#pragma once

#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

using namespace forte::core::io;

class LVGLNumberTextHandle : public IOHandle {
  public:
    LVGLNumberTextHandle(IODeviceController *paController,
                       IOMapper::Direction paDirection,
                       CIEC_ANY::EDataTypeID paType,
                       lv_obj_t *paWidget);

    ~LVGLNumberTextHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_obj_t *mWidget;
};
