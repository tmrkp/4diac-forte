#pragma once

#include "HMIDeviceController.h"
#include "HMIHandle.h"
#include "lvgl/lvgl.h"

class HMISpinBoxHandle : public HMIHandle {
  public:
    HMISpinBoxHandle(HMIDeviceController *paController, lv_obj_t *paObj);
    ~HMISpinBoxHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_obj_t *mObj;
};
