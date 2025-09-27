#include "LVGLSliderValueHandle.h"

#include "forte_dword.h"

LVGLSliderValueHandle::LVGLSliderValueHandle(IODeviceController *paController,
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

void LVGLSliderValueHandle::set(const CIEC_ANY &paState) {
}

void LVGLSliderValueHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    int32_t value = lv_slider_get_value(mWidget);
    static_cast<CIEC_DWORD &>(paState) = static_cast<CIEC_DWORD>(value);
  }
}

void LVGLSliderValueHandle::changeHandler(lv_event_t *e) {
  static_cast<LVGLSliderValueHandle *>(lv_event_get_user_data(e))->onChange();
}
