#include "HMIProgressBarHandle.h"

#include "startup.h"
#include "forte_dword.h"

HMIProgressBarHandle::HMIProgressBarHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::Out, CIEC_ANY::e_DWORD),
    mObj(paObj) {
}

void HMIProgressBarHandle::set(const CIEC_ANY &paState) {
  int32_t dword = static_cast<const CIEC_DWORD &>(paState);
  runLater([this, dword] { lv_bar_set_value(mObj, dword, false); });
}

void HMIProgressBarHandle::get(CIEC_ANY &paState) {
}
