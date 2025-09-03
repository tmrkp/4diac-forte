#pragma once

#include "HMIDeviceController.h"
#include "HMIHandle.h"
#include "lvgl/lvgl.h"

class HMIObserverHandle : public HMIHandle {
  public:
    HMIObserverHandle(HMIDeviceController *paController, lv_subject_t *paSubject);
    ~HMIObserverHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_subject_t *mSubject;
};
