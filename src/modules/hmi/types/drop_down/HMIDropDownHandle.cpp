#include "HMIDropDownHandle.h"

#include "forte_dword.h"

HMIDropDownHandle::HMIDropDownHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::In, CIEC_ANY::e_DWORD),
    mObj(paObj) {
  lv_obj_add_event_cb(paObj, changeHandler, LV_EVENT_VALUE_CHANGED, this);
}

void HMIDropDownHandle::set(const CIEC_ANY &paState) {
}

void HMIDropDownHandle::get(CIEC_ANY &paState) {
  static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(lv_dropdown_get_selected(mObj));
}
