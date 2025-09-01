#include "HMIBooleanIndicatorHandle.h"

#include "startup.h"

HMIBooleanIndicatorHandle::HMIBooleanIndicatorHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::Out, CIEC_ANY::e_BOOL),
    mObj(paObj) {
}

void HMIBooleanIndicatorHandle::set(const CIEC_ANY &paState) {
  bool on = static_cast<const CIEC_BOOL &>(paState);
  runLater([this, on] {
    if (on == true) {
      lv_led_on(mObj);
    } else {
      lv_led_off(mObj);
    }
  });
}

void HMIBooleanIndicatorHandle::get(CIEC_ANY &paState) {
}
