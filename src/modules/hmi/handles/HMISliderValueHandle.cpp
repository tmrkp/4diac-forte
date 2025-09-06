#include "HMISliderValueHandle.h"

#include "HMIDriver.h"
#include "forte_dword.h"

HMISliderValueHandle::HMISliderValueHandle(IODeviceController *paController,
                                           IOMapper::Direction paDirection,
                                           CIEC_ANY::EDataTypeID paType,
                                           lv_obj_t *paWidget,
                                           lv_event_code_t paEventCode) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
  if (paDirection == IOMapper::In) {
    lv_obj_add_event_cb(paWidget, changeHandler, paEventCode, this);
  }
}

void HMISliderValueHandle::set(const CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    uint32_t dword = static_cast<const CIEC_WORD &>(paState);
    HMIDriver::runLater([this, dword] { lv_slider_set_value(mWidget, dword, LV_ANIM_OFF); });
  }
}

void HMISliderValueHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    static_cast<CIEC_WORD &>(paState) = static_cast<CIEC_WORD>(lv_slider_get_value(mWidget));
  }
}

void HMISliderValueHandle::changeHandler(lv_event_t *e) {
  static_cast<HMISliderValueHandle *>(lv_event_get_user_data(e))->onChange();
}
