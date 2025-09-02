#include "HMIDeviceController.h"

#include "HMIDriver.h"

#include <iostream>
#include "lvgl/lvgl.h"

#include "HMIHandle.h"
#include "lvgl/src/core/lv_obj_class_private.h"
#include "types/boolean_indicator/HMIBooleanIndicatorHandle.h"
#include "types/button/HMIButtonHandle.h"
#include "types/check_box/HMICheckBoxHandle.h"
#include "types/drop_down/HMIDropDownHandle.h"
#include "types/number/HMINumberHandle.h"
#include "types/progress_bar/HMIProgressBarHandle.h"
#include "types/slider/HMISliderHandle.h"
#include "types/subject/HMISubjectHandle.h"
#include "types/switch/HMISwitchHandle.h"

HMIDeviceController::HMIDeviceController(CDeviceExecution &paDeviceExecution) :
    IODeviceMultiController(paDeviceExecution) {
}

void HMIDeviceController::setConfig(Config *paConfig) {
  this->mConfig = *static_cast<HMIConfig *>(paConfig);
}

const char *HMIDeviceController::init() {
  mGenerator.init();
  return nullptr;
}

IOHandle *HMIDeviceController::createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) {
  auto &desc(static_cast<HMIHandleDescriptor &>(paHandleDescriptor));

  switch (desc.mHandleType) {
    case SUBJECT: return createSubjectHandle(mGenerator.createSubjectWidget(&desc.mName));
    case BOOLEAN_INDICATOR:
      return createWidgetHandle<HMIBooleanIndicatorHandle>(mGenerator.createBooleanIndicatorWidget(desc.mLabel));
    case BUTTON: return createWidgetHandle<HMIButtonHandle>(mGenerator.createButtonWidget(desc.mLabel));
    case CHECK_BOX: return createWidgetHandle<HMICheckBoxHandle>(mGenerator.createCheckBoxWidget(desc.mLabel));
    case DROP_DOWN:
      return createWidgetHandle<HMIDropDownHandle>(mGenerator.createDropDownWidget(desc.mLabel, desc.mOptions));
    case NUMBER: return createWidgetHandle<HMINumberHandle>(mGenerator.createNumberWidget(desc.mLabel));
    case PROGRESS_BAR: return createWidgetHandle<HMIProgressBarHandle>(mGenerator.createProgressBarWidget(desc.mLabel));
    case SLIDER: return createWidgetHandle<HMISliderHandle>(mGenerator.createSliderWidget(desc.mLabel));
    case SWITCH: return createWidgetHandle<HMISwitchHandle>(mGenerator.createSwitchWidget(desc.mLabel));
  }

  // switch (desc.mHandleType) {
  //   case SUBJECT: return createSubjectHandle(findSubject(desc.mName));
  //   case BOOLEAN_INDICATOR: return createWidgetHandle<HMIBooleanIndicatorHandle>(findWidget(desc.mName,
  //   &lv_led_class)); case BUTTON: return createWidgetHandle<HMIButtonHandle>(findWidget(desc.mName,
  //   &lv_button_class)); case CHECK_BOX: return createWidgetHandle<HMICheckBoxHandle>(findWidget(desc.mName,
  //   &lv_checkbox_class)); case DROP_DOWN: return createWidgetHandle<HMIDropDownHandle>(findWidget(desc.mName,
  //   &lv_dropdown_class)); case NUMBER: return createWidgetHandle<HMINumberHandle>(findWidget(desc.mName,
  //   &lv_label_class)); case PROGRESS_BAR: return createWidgetHandle<HMIProgressBarHandle>(findWidget(desc.mName,
  //   &lv_bar_class)); case SLIDER: return createWidgetHandle<HMISliderHandle>(findWidget(desc.mName,
  //   &lv_slider_class)); case SWITCH: return createWidgetHandle<HMISwitchHandle>(findWidget(desc.mName,
  //   &lv_switch_class));
  // }
  return nullptr;
}

bool HMIDeviceController::isHandleValueEqual(IOHandle &paHandle) {
  return !static_cast<HMIHandle &>(paHandle).hasChanged();
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
    DEVLOG_WARNING("[HMIDeviceController] Unexpected type of widget with name '%s'. Expected type '%s'.\n",
                   paName.c_str(), paClass->name);
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

IOHandle *HMIDeviceController::createSubjectHandle(lv_subject_t *subject) {
  if (subject != nullptr) {
    return new HMISubjectHandle(this, subject);
  }
  return nullptr;
}
