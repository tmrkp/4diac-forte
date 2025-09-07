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
}

void HMISliderValueHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    int32_t value = lv_slider_get_value(mWidget);
    if (std::in_range<TForteDWord>(value)) {
      static_cast<CIEC_WORD &>(paState) = static_cast<CIEC_WORD>(value);
    } else {
      // TODO: How to handle this?
    }
  }
}

void HMISliderValueHandle::changeHandler(lv_event_t *e) {
  static_cast<HMISliderValueHandle *>(lv_event_get_user_data(e))->onChange();
}
