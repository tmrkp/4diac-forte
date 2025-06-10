#include "HMIDeviceController.h"

#include <iostream>

#include "HMIHandle.h"

HMIDeviceController::HMIDeviceController(CDeviceExecution &paDeviceExecution) :
  forte::core::io::IODeviceMultiController(paDeviceExecution) {
}

HMIDeviceController::~HMIDeviceController() {
  // do nothing
}

void HMIDeviceController::setConfig(struct forte::core::io::IODeviceController::Config *paConfig) {
  this->mConfig = *static_cast<HMIConfig *>(paConfig);
}

const char *HMIDeviceController::init() {
  return nullptr;
}

forte::core::io::IOHandle *
HMIDeviceController::createIOHandle(forte::core::io::IODeviceController::HandleDescriptor &paHandleDescriptor) {
  HMIHandleDescriptor &desc(static_cast<HMIHandleDescriptor &>(paHandleDescriptor));

  return new HMIHandle(this, desc.mType, desc.mDirection);
}

void HMIDeviceController::deInit() {

}

void HMIDeviceController::runLoop() {
  while (isAlive()) {
    sleepThread(1000);
    std::cout << "Hello from HMIDeviceController" << std::endl;
  }
}

void HMIDeviceController::addSlaveHandle(size_t paIndex, std::unique_ptr<forte::core::io::IOHandle> paHandle) {
  CCriticalRegion criticalRegion(mHandleMutex);
  paHandle->isInput() ? mInputHandles.push_back(std::move(paHandle)) : mOutputHandles.push_back(std::move(paHandle));
}

void HMIDeviceController::dropSlaveHandles(size_t) {
  // Is handled by #dropHandles method
}

bool HMIDeviceController::isSlaveAvailable(size_t paIndex) {

}

bool HMIDeviceController::checkSlaveType(size_t paIndex, int paType) {

}

