#include "HMIHandle.h"

HMIHandle::HMIHandle(HMIDeviceController *paController, IOMapper::Direction paDirection, CIEC_ANY::EDataTypeID paType) :
    IOHandle(paController, paDirection, paType) {
}

bool HMIHandle::hasChanged() {
  if (mHasChanged) {
    mHasChanged = false;
    return true;
  }
  return false;
}

void HMIHandle::changeHandler(lv_event_t *e) {
  static_cast<HMIHandle *>(lv_event_get_user_data(e))->mHasChanged = true;
}
