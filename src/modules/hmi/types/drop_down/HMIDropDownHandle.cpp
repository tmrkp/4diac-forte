#include "HMIDropDownHandle.h"

HMIDropDownHandle::HMIDropDownHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::In, CIEC_ANY::e_DWORD),
    mObj(paObj) {
  lv_obj_add_event_cb(paObj, changeHandler, LV_EVENT_VALUE_CHANGED, this);
}

void HMIDropDownHandle::set(const CIEC_ANY &paState) {
}

void HMIDropDownHandle::get(CIEC_ANY &paState) {
  static_cast<CIEC_BOOL &>(paState) = CIEC_BOOL(lv_dropdown_get_selected(mObj));
}
