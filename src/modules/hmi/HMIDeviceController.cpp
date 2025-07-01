#include "HMIDeviceController.h"

#include <iostream>

#include "HMIHandle.h"

HMIDeviceController::HMIDeviceController(CDeviceExecution &paDeviceExecution) :
    IODeviceMultiController(paDeviceExecution) {
}

HMIDeviceController::~HMIDeviceController() {
  // do nothing
}

void HMIDeviceController::setConfig(Config *paConfig) {
  this->mConfig = *static_cast<HMIConfig *>(paConfig);
}

const char *HMIDeviceController::init() {
  return nullptr;
}

IOHandle *HMIDeviceController::createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) {
  auto &desc(static_cast<HMIHandleDescriptor &>(paHandleDescriptor));

  return new HMIHandle(this, desc.mType, desc.mDirection);
}

bool HMIDeviceController::isHandleValueEqual(IOHandle &paHandle) {
  return !static_cast<HMIHandle &>(paHandle).hasChanged();
}

void HMIDeviceController::deInit() {
}

void HMIDeviceController::runLoop() {
  while (isAlive()) {
    sleepThread(250);
    checkForInputChanges();
  }
}

void HMIDeviceController::addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) {
  CCriticalRegion criticalRegion(mHandleMutex);
  paHandle->isInput() ? mInputHandles.push_back(std::move(paHandle)) : mOutputHandles.push_back(std::move(paHandle));
}

void HMIDeviceController::dropSlaveHandles(size_t) {
  // Is handled by #dropHandles method
}

bool HMIDeviceController::isSlaveAvailable(size_t paIndex) {
  return true;
}

bool HMIDeviceController::checkSlaveType(size_t paIndex, int paType) {
  return true;
}
