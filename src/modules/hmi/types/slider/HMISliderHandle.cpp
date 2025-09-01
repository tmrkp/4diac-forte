#include "HMISliderHandle.h"

#include "forte_dword.h"

HMISliderHandle::HMISliderHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::In, CIEC_ANY::e_DWORD),
    mObj(paObj) {
  lv_obj_add_event_cb(paObj, changeHandler, LV_EVENT_VALUE_CHANGED, this);
}

void HMISliderHandle::set(const CIEC_ANY &paState) {
}

void HMISliderHandle::get(CIEC_ANY &paState) {
  static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(lv_slider_get_value(mObj));
}
