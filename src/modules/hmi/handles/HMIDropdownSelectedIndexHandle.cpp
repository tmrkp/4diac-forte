#include "HMIDropdownSelectedIndexHandle.h"

#include "HMIDriver.h"
#include "forte_dword.h"

HMIDropdownSelectedIndexHandle::HMIDropdownSelectedIndexHandle(IODeviceController *paController,
                                                               IOMapper::Direction paDirection,
                                                               CIEC_ANY::EDataTypeID paType,
                                                               lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
  if (paDirection == IOMapper::In) {
    lv_obj_add_event_cb(paWidget, changeHandler, LV_EVENT_VALUE_CHANGED, this);
  }
}

void HMIDropdownSelectedIndexHandle::set(const CIEC_ANY &paState) {
}

void HMIDropdownSelectedIndexHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    static_cast<CIEC_DWORD &>(paState) = static_cast<CIEC_DWORD>(lv_dropdown_get_selected(mWidget));
  }
}

void HMIDropdownSelectedIndexHandle::changeHandler(lv_event_t *e) {
  static_cast<HMIDropdownSelectedIndexHandle *>(lv_event_get_user_data(e))->onChange();
}
