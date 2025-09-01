#pragma once

#include "HMIDeviceController.h"
#include "HMIHandle.h"
#include "lvgl/lvgl.h"

class HMIButtonHandle : public HMIHandle {
  public:
    HMIButtonHandle(HMIDeviceController *paController, lv_obj_t *paObj);
    ~HMIButtonHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;
};
