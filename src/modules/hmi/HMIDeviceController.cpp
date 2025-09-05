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
  // mGenerator.init();
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

lv_obj_t *HMIDeviceController::findWidget(const std::string &paName, const lv_obj_class_t *paClass) {
  lv_obj_t *obj = lv_obj_find_by_name(lv_screen_active(), paName.c_str());
  if (obj == nullptr) {
    DEVLOG_WARNING("[HMIDeviceController] Cannot find widget with name '%s'\n", paName.c_str());
    return nullptr;
  }
  if (lv_obj_get_class(obj) != paClass) {
    DEVLOG_WARNING("[HMIDeviceController] Unexpected widget with name '%s'\n", paName.c_str());
    return nullptr;
  }
  return obj;
}

lv_subject_t *HMIDeviceController::findSubject(const std::string &paName) {
  lv_subject_t *subject = lv_xml_get_subject(nullptr, paName.c_str());

  if (subject == nullptr) {
    DEVLOG_WARNING("[HMIDeviceController] Cannot find subject '%s'\n", paName.c_str());
    return nullptr;
  }

  return subject;
}
