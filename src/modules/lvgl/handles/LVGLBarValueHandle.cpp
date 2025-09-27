#include "LVGLBarValueHandle.h"

#include "LVGLDeviceController.h"
#include "forte_dword.h"

LVGLBarValueHandle::LVGLBarValueHandle(IODeviceController *paController,
                                       IOMapper::Direction paDirection,
                                       CIEC_ANY::EDataTypeID paType,
                                       lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
}

void LVGLBarValueHandle::set(const CIEC_ANY &paState) {
  auto *controller = static_cast<LVGLDeviceController *>(mController);
  if (mType == CIEC_ANY::e_DWORD) {
    TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
    controller->runLater(
        [this, value = static_cast<int32_t>(dword)] { lv_bar_set_value(mWidget, value, LV_ANIM_OFF); });
  }
}

void LVGLBarValueHandle::get(CIEC_ANY &paState) {
}
