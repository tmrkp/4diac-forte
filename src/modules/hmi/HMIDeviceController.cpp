#include "HMIDeviceController.h"

#include "HMISubjectHandle.h"

#include <iostream>
#include "lvgl/lvgl.h"

#include "HMIWidgetHandle.h"
#include "HMISubjectHandle.h"

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

  if (desc.mTargetType == HMIHandleDescriptor::TargetType::WIDGET) {
    return new HMIWidgetHandle(this, desc.mType, desc.mDirection, desc.mName);
  }
  if (desc.mTargetType == HMIHandleDescriptor::TargetType::SUBJECT) {
    return new HMISubjectHandle(this, desc.mType, desc.mDirection, desc.mName);
  }
  return nullptr;
}

bool HMIDeviceController::isHandleValueEqual(IOHandle &paHandle) {
  return !static_cast<HMIWidgetHandle &>(paHandle).hasChanged();
}

void HMIDeviceController::deInit() {
}

void HMIDeviceController::runLoop() {
  while (isAlive()) {
    sleepThread(1000 / 60);
    checkForInputChanges();
  }
}

void HMIDeviceController::addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) {
  CCriticalRegion criticalRegion(mHandleMutex);
  paHandle->isInput() ? mInputHandles.push_back(std::move(paHandle)) : mOutputHandles.push_back(std::move(paHandle));
}

void HMIDeviceController::dropSlaveHandles(size_t) {
  // TODO: might need to be implemented
}

bool HMIDeviceController::isSlaveAvailable(size_t paIndex) {
  return true;
}

bool HMIDeviceController::checkSlaveType(size_t paIndex, int paType) {
  return true;
}
