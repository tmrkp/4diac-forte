#pragma once

#include "HMIDeviceController.h"
#include "HMIHandle.h"
#include "lvgl/lvgl.h"

class HMINumberHandle : public HMIHandle {
  public:
    HMINumberHandle(HMIDeviceController *paController, lv_obj_t *paObj);
    ~HMINumberHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_obj_t *mObj;
};
