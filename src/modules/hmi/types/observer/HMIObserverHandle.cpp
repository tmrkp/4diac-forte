#include "HMIObserverHandle.h"

#include "forte_dword.h"

HMIObserverHandle::HMIObserverHandle(HMIDeviceController *paController, lv_subject_t *paSubject) :
    HMIHandle(paController, IOMapper::In, CIEC_ANY::e_DWORD),
    mSubject(paSubject) {
  lv_subject_add_observer(paSubject, changeHandler, this);
}

void HMIObserverHandle::set(const CIEC_ANY &paState) {
}

void HMIObserverHandle::get(CIEC_ANY &paState) {
  static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(lv_subject_get_int(mSubject));
}
