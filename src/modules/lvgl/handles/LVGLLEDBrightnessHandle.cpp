#include "LVGLLEDBrightnessHandle.h"

#include "LVGLDeviceController.h"
#include "LVGLDriver.h"
#include "forte_dword.h"

LVGLLEDBrightnessHandle::LVGLLEDBrightnessHandle(IODeviceController *paController,
                                                 CIEC_ANY::EDataTypeID paType,
                                                 lv_obj_t *paWidget) :
    IOHandle(paController, IOMapper::Out, paType),
    mWidget(paWidget) {
}

void LVGLLEDBrightnessHandle::set(const CIEC_ANY &paState) {
  auto *controller = static_cast<LVGLDeviceController *>(mController);
  if (mType == CIEC_ANY::e_BOOL) {
    bool on = static_cast<const CIEC_BOOL &>(paState);
    controller->runLater([this, on] {
      if (on) {
        lv_led_on(mWidget);
      } else {
        lv_led_off(mWidget);
      }
    });
  } else if (mType == CIEC_ANY::e_BYTE) {
    TForteByte byte = static_cast<const CIEC_BYTE &>(paState);
    controller->runLater([this, byte] { lv_led_set_brightness(mWidget, byte); });
  }
}

void LVGLLEDBrightnessHandle::get(CIEC_ANY &paState) {
}
