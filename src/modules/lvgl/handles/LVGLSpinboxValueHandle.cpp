#include "LVGLSpinboxValueHandle.h"

#include "LVGLDriver.h"
#include "forte_dword.h"

LVGLSpinboxValueHandle::LVGLSpinboxValueHandle(IODeviceController *paController,
                                             IOMapper::Direction paDirection,
                                             CIEC_ANY::EDataTypeID paType,
                                             lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
  if (paDirection == IOMapper::In) {
    lv_obj_add_event_cb(paWidget, changeHandler, LV_EVENT_VALUE_CHANGED, this);
  }
}

void LVGLSpinboxValueHandle::set(const CIEC_ANY &paState) {
}

void LVGLSpinboxValueHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    static_cast<CIEC_DWORD &>(paState) = static_cast<CIEC_DWORD>(lv_spinbox_get_value(mWidget));
  }
}

void LVGLSpinboxValueHandle::changeHandler(lv_event_t *e) {
  static_cast<LVGLSpinboxValueHandle *>(lv_event_get_user_data(e))->onChange();
}
