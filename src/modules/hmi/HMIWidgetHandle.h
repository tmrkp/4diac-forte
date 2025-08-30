#pragma once

#include "HMIDeviceController.h"
#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

class HMIWidgetHandle : public IOHandle {
  public:
    HMIWidgetHandle(HMIDeviceController *paController,
                    CIEC_ANY::EDataTypeID paType,
                    IOMapper::Direction paDirection,
                    std::string const &paName);

    ~HMIWidgetHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

    bool hasChanged();

  private:
    std::string const &mName;
    lv_obj_t *mObj;
    bool mHasChanged = false;

    static void changeHandler(lv_event_t *e);
};
