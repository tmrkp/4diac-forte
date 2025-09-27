#include "LVGLNumberTextHandle.h"

#include "LVGLDeviceController.h"
#include "forte_dword.h"

LVGLNumberTextHandle::LVGLNumberTextHandle(IODeviceController *paController,
                                           IOMapper::Direction paDirection,
                                           CIEC_ANY::EDataTypeID paType,
                                           lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
}

void LVGLNumberTextHandle::set(const CIEC_ANY &paState) {
  auto *controller = static_cast<LVGLDeviceController *>(mController);
  if (mType == CIEC_ANY::e_DWORD) {
    TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
    controller->runLater([this, value = static_cast<uint32_t>(dword)] { lv_label_set_text_fmt(mWidget, "%d", value); });
  }
}

void LVGLNumberTextHandle::get(CIEC_ANY &paState) {
}
