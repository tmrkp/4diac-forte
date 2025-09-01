#include "HMICheckBoxHandle.h"

#include "forte_dword.h"

HMICheckBoxHandle::HMICheckBoxHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::In, CIEC_ANY::e_BOOL),
    mObj(paObj) {
  lv_obj_add_event_cb(paObj, changeHandler, LV_EVENT_VALUE_CHANGED, this);
}

void HMICheckBoxHandle::set(const CIEC_ANY &paState) {
}

void HMICheckBoxHandle::get(CIEC_ANY &paState) {
  static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(lv_obj_has_state(mObj, LV_STATE_CHECKED));
}
