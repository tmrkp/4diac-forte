#include "HMILabelTextHandle.h"

#include "HMIDriver.h"
#include "forte_dword.h"

HMILabelTextHandle::HMILabelTextHandle(IODeviceController *paController,
                                       IOMapper::Direction paDirection,
                                       CIEC_ANY::EDataTypeID paType,
                                       lv_obj_t *paWidget,
                                       const char *paFmt) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget),
    mFmt(paFmt) {
}

void HMILabelTextHandle::set(const CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    uint32_t dword = static_cast<const CIEC_DWORD &>(paState);
    HMIDriver::runLater([this, dword] { lv_label_set_text_fmt(mWidget, mFmt, dword); });
  }
}

void HMILabelTextHandle::get(CIEC_ANY &paState) {
}
