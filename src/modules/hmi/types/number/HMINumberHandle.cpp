#include "HMINumberHandle.h"

#include "HMIDriver.h"
#include "forte_dword.h"

HMINumberHandle::HMINumberHandle(HMIDeviceController *paController, lv_obj_t *paObj) :
    HMIHandle(paController, IOMapper::Out, CIEC_ANY::e_DWORD),
    mObj(paObj) {
}

void HMINumberHandle::set(const CIEC_ANY &paState) {
  uint32_t dword = static_cast<const CIEC_DWORD &>(paState);
  HMIDriver::runLater([this, dword] { lv_label_set_text_fmt(mObj, "%d", dword); });
}

void HMINumberHandle::get(CIEC_ANY &paState) {
}
