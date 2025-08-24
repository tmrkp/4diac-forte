#pragma once

#include "HMIDeviceController.h"
#include "io/mapper/io_handle.h"

using TargetType = HMIDeviceController::HMIHandleDescriptor::TargetType;

class HMIHandle : public IOHandle {
  public:
    HMIHandle(HMIDeviceController *paController,
              CIEC_ANY::EDataTypeID paType,
              IOMapper::Direction paDirection,
              TargetType paTargetType,
              std::string const &paName);

    ~HMIHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

    bool hasChanged();

  private:
    TargetType mTargetType;
    std::string const &mName;
    bool mHasChanged = false;
};
