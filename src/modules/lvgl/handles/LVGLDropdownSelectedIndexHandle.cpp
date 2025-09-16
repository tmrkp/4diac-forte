#include "LVGLDropdownSelectedIndexHandle.h"

#include "LVGLDriver.h"
#include "forte_dword.h"

LVGLDropdownSelectedIndexHandle::LVGLDropdownSelectedIndexHandle(IODeviceController *paController,
                                                               IOMapper::Direction paDirection,
                                                               CIEC_ANY::EDataTypeID paType,
                                                               lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
  if (paDirection == IOMapper::In) {
    lv_obj_add_event_cb(paWidget, changeHandler, LV_EVENT_VALUE_CHANGED, this);
  }
}

void LVGLDropdownSelectedIndexHandle::set(const CIEC_ANY &paState) {
}

void LVGLDropdownSelectedIndexHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    uint32_t value = lv_dropdown_get_selected(mWidget);
    static_cast<CIEC_DWORD &>(paState) = static_cast<CIEC_DWORD>(value);
  }
}

void LVGLDropdownSelectedIndexHandle::changeHandler(lv_event_t *e) {
  static_cast<LVGLDropdownSelectedIndexHandle *>(lv_event_get_user_data(e))->onChange();
}
