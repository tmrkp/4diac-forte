#include "LVGLSubjectHandle.h"

#include "forte_any.h"
#include "forte_dword.h"
#include "LVGLDriver.h"

LVGLSubjectHandle::LVGLSubjectHandle(IODeviceController *paController,
                                   IOMapper::Direction paDirection,
                                   lv_subject_t *paSubject) :
    IOHandle(paController, paDirection, CIEC_ANY::e_DWORD),
    mSubject(paSubject) {
  if (paDirection == IOMapper::In) {
    lv_subject_add_observer(paSubject, changeHandler, this);
  }
}

void LVGLSubjectHandle::get(CIEC_ANY &paState) {
  int32_t value = lv_subject_get_int(mSubject);
  static_cast<CIEC_DWORD &>(paState) = static_cast<CIEC_DWORD>(value);
}

void LVGLSubjectHandle::set(const CIEC_ANY &paState) {
  TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
  LVGLDriver::runLater([this, value = static_cast<int32_t>(dword)] { lv_subject_set_int(mSubject, value); });
}

void LVGLSubjectHandle::changeHandler(lv_observer_t *observer, lv_subject_t *subject) {
  static_cast<IOHandle *>(lv_observer_get_user_data(observer))->onChange();
}
