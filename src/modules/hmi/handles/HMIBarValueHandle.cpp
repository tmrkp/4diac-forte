#include "HMIBarValueHandle.h"

#include "HMIDriver.h"
#include "forte_dword.h"

HMIBarValueHandle::HMIBarValueHandle(IODeviceController *paController,
                                     IOMapper::Direction paDirection,
                                     CIEC_ANY::EDataTypeID paType,
                                     lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
}

void HMIBarValueHandle::set(const CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    uint32_t dword = static_cast<const CIEC_WORD &>(paState);
    HMIDriver::runLater([this, dword] { lv_bar_set_value(mWidget, dword, LV_ANIM_OFF); });
  }
}

void HMIBarValueHandle::get(CIEC_ANY &paState) {
}
