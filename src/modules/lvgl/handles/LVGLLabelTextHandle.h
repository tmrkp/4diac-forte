#pragma once

#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

using namespace forte::core::io;

class LVGLLabelTextHandle : public IOHandle {
  public:
    LVGLLabelTextHandle(IODeviceController *paController,
                       IOMapper::Direction paDirection,
                       CIEC_ANY::EDataTypeID paType,
                       lv_obj_t *paWidget,
                       const char *paFmt);

    ~LVGLLabelTextHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_obj_t *mWidget;
    const char *mFmt;
};
