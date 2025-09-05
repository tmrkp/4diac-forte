#include "HMISubjectHandle.h"

#include "forte_any.h"
#include "forte_dword.h"
#include "HMIDriver.h"

HMISubjectHandle::HMISubjectHandle(IODeviceController *paController,
                                   IOMapper::Direction paDirection,
                                   lv_subject_t *paSubject) :
    IOHandle(paController, paDirection, CIEC_ANY::e_DWORD),
    mSubject(paSubject) {
  if (paDirection == IOMapper::In) {
    lv_subject_add_observer(paSubject, changeHandler, this);
  }
}

void HMISubjectHandle::get(CIEC_ANY &paState) {
  static_cast<CIEC_DWORD &>(paState) = static_cast<CIEC_DWORD>(lv_subject_get_int(mSubject));
}

void HMISubjectHandle::set(const CIEC_ANY &paState) {
  int32_t dword = static_cast<const CIEC_DWORD &>(paState);
  HMIDriver::runLater([this, dword] { lv_subject_set_int(mSubject, dword); });
}

void HMISubjectHandle::changeHandler(lv_observer_t *observer, lv_subject_t *subject) {
  static_cast<IOHandle *>(lv_observer_get_user_data(observer))->onChange();
}
