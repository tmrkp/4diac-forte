#include "LVGLWidgetStateHandle.h"

#include "LVGLDriver.h"

LVGLWidgetStateHandle::LVGLWidgetStateHandle(IODeviceController *paController,
                                           IOMapper::Direction paDirection,
                                           CIEC_ANY::EDataTypeID paType,
                                           lv_obj_t *paWidget,
                                           lv_state_t paState,
                                           lv_event_code_t paEventCode) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget),
    mState(paState) {
  if (paDirection == IOMapper::In) {
    lv_obj_add_event_cb(paWidget, changeHandler, paEventCode, this);
  }
}

void LVGLWidgetStateHandle::set(const CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_BOOL) {
    bool on = static_cast<const CIEC_BOOL &>(paState);
    LVGLDriver::runLater([this, on] { lv_obj_set_state(mWidget, mState, on); });
  }
}

void LVGLWidgetStateHandle::get(CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_BOOL) {
    static_cast<CIEC_BOOL &>(paState) = static_cast<CIEC_BOOL>(lv_obj_has_state(mWidget, mState));
  }
}

void LVGLWidgetStateHandle::changeHandler(lv_event_t *e) {
  static_cast<LVGLWidgetStateHandle *>(lv_event_get_user_data(e))->onChange();
}
