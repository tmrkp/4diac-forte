#include "LVGLLabelTextHandle.h"

#include "LVGLDriver.h"
#include "forte_dword.h"

LVGLLabelTextHandle::LVGLLabelTextHandle(IODeviceController *paController,
                                       IOMapper::Direction paDirection,
                                       CIEC_ANY::EDataTypeID paType,
                                       lv_obj_t *paWidget,
                                       const char *paFmt) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget),
    mFmt(paFmt) {
}

void LVGLLabelTextHandle::set(const CIEC_ANY &paState) {
  if (mType == CIEC_ANY::e_DWORD) {
    TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
    LVGLDriver::runLater([this, value = static_cast<uint32_t>(dword)] { lv_label_set_text_fmt(mWidget, mFmt, value); });
  }
}

void LVGLLabelTextHandle::get(CIEC_ANY &paState) {
}
