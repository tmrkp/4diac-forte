#pragma once

#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

using namespace forte::core::io;

class HMISpinboxValueHandle : public IOHandle {
  public:
    HMISpinboxValueHandle(IODeviceController *paController,
                          IOMapper::Direction paDirection,
                          CIEC_ANY::EDataTypeID paType,
                          lv_obj_t *paWidget);

    ~HMISpinboxValueHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    static void changeHandler(lv_event_t *e);

    lv_obj_t *mWidget;
};
