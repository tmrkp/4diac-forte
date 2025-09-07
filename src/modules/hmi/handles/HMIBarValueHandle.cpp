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
    TForteDWord dword = static_cast<const CIEC_WORD &>(paState);
    if (std::in_range<int32_t>(dword)) {
      HMIDriver::runLater(
          [this, value = static_cast<int32_t>(dword)] { lv_bar_set_value(mWidget, value, LV_ANIM_OFF); });
    } else {
      // TODO: How to handle this?
    }
  }
}

void HMIBarValueHandle::get(CIEC_ANY &paState) {
}
