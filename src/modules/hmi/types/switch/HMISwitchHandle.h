#pragma once

#include "HMIDeviceController.h"
#include "HMIHandle.h"
#include "lvgl/lvgl.h"

class HMISwitchHandle : public HMIHandle {
  public:
    HMISwitchHandle(HMIDeviceController *paController, lv_obj_t *paObj);
    ~HMISwitchHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_obj_t *mObj;
};
