#include "HMIHandle.h"

extern void hmi_set_led(bool);
extern bool hmi_button_was_pressed();

HMIHandle::HMIHandle(HMIDeviceController *paController, CIEC_ANY::EDataTypeID paType, IOMapper::Direction paDirection):
  IOHandle(paController, paDirection, paType) {
}

HMIHandle::~HMIHandle() {

}

void HMIHandle::set(const CIEC_ANY &paState) {
  hmi_set_led(static_cast<const CIEC_BOOL &>(paState));
}

void HMIHandle::get(CIEC_ANY &paState) {

}

bool HMIHandle::hasChanged() {
  return hmi_button_was_pressed();
}

