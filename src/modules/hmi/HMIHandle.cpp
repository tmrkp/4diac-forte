#include "HMIHandle.h"

HMIHandle::HMIHandle(HMIDeviceController *paController, IOMapper::Direction paDirection, CIEC_ANY::EDataTypeID paType) :
    IOHandle(paController, paDirection, paType) {
}

void HMIHandle::changeHandler(lv_event_t *e) {
  static_cast<HMIHandle *>(lv_event_get_user_data(e))->onChange();
}

void HMIHandle::changeHandler(lv_observer_t *observer, lv_subject_t *subject) {
  static_cast<IOHandle *>(lv_observer_get_user_data(observer))->onChange();
}
