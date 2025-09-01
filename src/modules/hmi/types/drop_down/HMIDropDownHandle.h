#pragma once

#include "HMIDeviceController.h"
#include "HMIHandle.h"
#include "lvgl/lvgl.h"

class HMIDropDownHandle : public HMIHandle {
  public:
    HMIDropDownHandle(HMIDeviceController *paController, lv_obj_t *paObj);
    ~HMIDropDownHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_obj_t *mObj;
};
