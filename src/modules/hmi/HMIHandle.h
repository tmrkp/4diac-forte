#pragma once

#include "HMIDeviceController.h"
#include "io/mapper/io_handle.h"

class HMIHandle : public IOHandle {
  public:
    HMIHandle(HMIDeviceController *paController,
              CIEC_ANY::EDataTypeID paType,
              IOMapper::Direction paDirection,
              std::string const &paWidgetName);

    ~HMIHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

    bool hasChanged();

  private:
    std::string const &mWidgetName;
    bool mHasChanged = false;
};
