#pragma once

#include "HMIDeviceController.h"
#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

class HMISubjectHandle : public IOHandle {
  public:
    HMISubjectHandle(HMIDeviceController *paController,
                     CIEC_ANY::EDataTypeID paType,
                     IOMapper::Direction paDirection,
                     std::string const &paName);

    ~HMISubjectHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

    bool hasChanged();

  private:
    std::string const &mName;
    lv_subject_t *mSubject;
};
