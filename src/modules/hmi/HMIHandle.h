#pragma once

#include "HMIDeviceController.h"
#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

class HMIHandle : public IOHandle {
  public:
    HMIHandle(HMIDeviceController *paController, IOMapper::Direction paDirection, CIEC_ANY::EDataTypeID paType);

    bool hasChanged();

  protected:
    bool mHasChanged = false;

    static void changeHandler(lv_event_t *e);
};
