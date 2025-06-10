#pragma once

#include "HMIDeviceController.h"
#include "io/mapper/io_handle.h"

class HMIHandle : public forte::core::io::IOHandle {
  public:
    HMIHandle(HMIDeviceController *paController,
              CIEC_ANY::EDataTypeID paType,
              forte::core::io::IOMapper::Direction paDirection);

    ~HMIHandle();

    virtual void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;
};
