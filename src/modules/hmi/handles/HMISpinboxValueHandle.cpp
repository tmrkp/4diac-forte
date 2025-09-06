#include "HMISpinboxValueHandle.h"

#include "HMIDriver.h"
#include "forte_dword.h"

HMISpinboxValueHandle::HMISpinboxValueHandle(IODeviceController *paController,
                                             IOMapper::Direction paDirection,
                                             CIEC_ANY::EDataTypeID paType,
                                             lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
  if (paDirection == IOMapper::In) {
    lv_obj_add_event_cb(paWidget, changeHandler, LV_EVENT_VALUE_CHANGED, this);
  }
}

void HMISpinboxValueHandle::set(const CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    uint32_t dword = static_cast<const CIEC_WORD &>(paState);
    HMIDriver::runLater([this, dword] { lv_spinbox_set_value(mWidget, dword); });
  }
}

void HMISpinboxValueHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    static_cast<CIEC_WORD &>(paState) = static_cast<CIEC_WORD>(lv_spinbox_get_value(mWidget));
  }
}

void HMISpinboxValueHandle::changeHandler(lv_event_t *e) {
  static_cast<HMISpinboxValueHandle *>(lv_event_get_user_data(e))->onChange();
}
