#include "HMISubjectHandle.h"

#include "forte_dword.h"
#include "HMIDriver.h"

HMISubjectHandle::HMISubjectHandle(HMIDeviceController *paController, lv_subject_t *paSubject) :
    HMIHandle(paController, IOMapper::Out, CIEC_ANY::e_DWORD),
    mSubject(paSubject) {
}

void HMISubjectHandle::set(const CIEC_ANY &paState) {
  int32_t dword = static_cast<const CIEC_DWORD &>(paState);
  HMIDriver::runLater([this, dword] { lv_subject_set_int(mSubject, dword); });
}

void HMISubjectHandle::get(CIEC_ANY &paState) {
}
