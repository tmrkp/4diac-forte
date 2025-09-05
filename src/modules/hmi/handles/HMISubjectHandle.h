#pragma once

#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

using namespace forte::core::io;

class HMISubjectHandle : public IOHandle {
  public:
    HMISubjectHandle(IODeviceController *paController, IOMapper::Direction paDirection, lv_subject_t *paSubject);

    ~HMISubjectHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    static void changeHandler(lv_observer_t *observer, lv_subject_t *subject);

    lv_subject_t *mSubject;
};
