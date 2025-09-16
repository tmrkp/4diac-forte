#include "LVGLDeviceController.h"

#include "LVGLDriver.h"

#include <iostream>
#include "lvgl/lvgl.h"

LVGLDeviceController::LVGLDeviceController(CDeviceExecution &paDeviceExecution) :
    IODeviceMultiController(paDeviceExecution) {
}

void LVGLDeviceController::setConfig(Config *paConfig) {
  this->mConfig = *static_cast<LVGLConfig *>(paConfig);
}

const char *LVGLDeviceController::init() {
  mConnector.init();
  return nullptr;
}

IOHandle *LVGLDeviceController::createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) {
  return static_cast<LVGLHandleDescriptor *>(&paHandleDescriptor)->createIOHandle(this);
}

void LVGLDeviceController::deInit() {
}

void LVGLDeviceController::runLoop() {
}

void LVGLDeviceController::addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) {
  CCriticalRegion criticalRegion(mHandleMutex);
  paHandle->isInput() ? mInputHandles.push_back(std::move(paHandle)) : mOutputHandles.push_back(std::move(paHandle));
}

void LVGLDeviceController::dropSlaveHandles(size_t) {
}

bool LVGLDeviceController::isSlaveAvailable(size_t paIndex) {
  return true;
}

bool LVGLDeviceController::checkSlaveType(size_t paIndex, int paType) {
  return true;
}
