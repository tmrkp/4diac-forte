#include "HMIDeviceController.h"

#include "HMIDriver.h"

#include <iostream>
#include "lvgl/lvgl.h"

HMIDeviceController::HMIDeviceController(CDeviceExecution &paDeviceExecution) :
    IODeviceMultiController(paDeviceExecution) {
}

void HMIDeviceController::setConfig(Config *paConfig) {
  this->mConfig = *static_cast<HMIConfig *>(paConfig);
}

const char *HMIDeviceController::init() {
  mConnector.init();
  return nullptr;
}

IOHandle *HMIDeviceController::createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) {
  return static_cast<HMIHandleDescriptor *>(&paHandleDescriptor)->createIOHandle(this);
}

void HMIDeviceController::deInit() {
}

void HMIDeviceController::runLoop() {
}

void HMIDeviceController::addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) {
  CCriticalRegion criticalRegion(mHandleMutex);
  paHandle->isInput() ? mInputHandles.push_back(std::move(paHandle)) : mOutputHandles.push_back(std::move(paHandle));
}

void HMIDeviceController::dropSlaveHandles(size_t) {
}

bool HMIDeviceController::isSlaveAvailable(size_t paIndex) {
  return true;
}

bool HMIDeviceController::checkSlaveType(size_t paIndex, int paType) {
  return true;
}
