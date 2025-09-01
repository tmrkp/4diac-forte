#pragma once

#include "HMIDeviceController.h"
#include "HMIHandle.h"
#include "lvgl/lvgl.h"

class HMISubjectHandle : public HMIHandle {
  public:
    HMISubjectHandle(HMIDeviceController *paController, lv_subject_t *paSubject);
    ~HMISubjectHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_subject_t *mSubject;
};
