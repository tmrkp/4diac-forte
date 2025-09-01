#include "HMIButtonHandle.h"

HMIButtonHandle::HMIButtonHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::In, CIEC_ANY::e_Max) {
  lv_obj_add_event_cb(paObj, changeHandler, LV_EVENT_CLICKED, this);
}

void HMIButtonHandle::set(const CIEC_ANY &paState) {
}

void HMIButtonHandle::get(CIEC_ANY &paState) {
}
