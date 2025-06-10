#include "HMIHandle.h"

HMIHandle::HMIHandle(HMIDeviceController *paController,
                     CIEC_ANY::EDataTypeID paType,
                     forte::core::io::IOMapper::Direction paDirection):
  IOHandle(paController, paDirection, paType) {

}

HMIHandle::~HMIHandle() {

}

void HMIHandle::set(const CIEC_ANY &) {

}

void HMIHandle::get(CIEC_ANY &) {

}

