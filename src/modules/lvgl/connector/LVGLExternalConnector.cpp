#include "LVGLExternalConnector.h"

#include "LVGLDriver.h"
#include "devlog.h"

void LVGLExternalConnector::init() {
}

lv_obj_t *LVGLExternalConnector::connectButton(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_button_class);
}

lv_obj_t *LVGLExternalConnector::connectChart(const std::string &paName,
                                             const std::string &paLabel,
                                             int32_t paMinYRange,
                                             int32_t paMaxYRange,
                                             uint32_t paPointCount) {
  if (lv_obj_t *widget = findWidget(paName, &lv_chart_class)) {
    LVGLDriver::runLater([widget, paMinYRange, paMaxYRange, paPointCount] {
      lv_chart_set_point_count(widget, paPointCount);
      lv_chart_set_axis_range(widget, LV_CHART_AXIS_PRIMARY_Y, paMinYRange, paMaxYRange);
    });
  }
  return nullptr;
}

lv_obj_t *LVGLExternalConnector::connectCheckbox(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_checkbox_class);
}

lv_obj_t *LVGLExternalConnector::connectDropdown(const std::string &paName,
                                                const std::string &paLabel,
                                                const std::string &paOptions) {
  return findWidget(paName, &lv_dropdown_class);
}

lv_obj_t *LVGLExternalConnector::connectLED(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_led_class);
}

lv_obj_t *LVGLExternalConnector::connectNumber(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_label_class);
}

lv_subject_t *LVGLExternalConnector::connectObserver(const std::string &paName) {
  return findSubject(paName);
}

lv_obj_t *LVGLExternalConnector::connectProgressbar(const std::string &paName,
                                                   const std::string &paLabel,
                                                   int32_t paMinRange,
                                                   int32_t paMaxRange) {
  if (lv_obj_t *widget = findWidget(paName, &lv_bar_class)) {
    LVGLDriver::runLater([widget, paMinRange, paMaxRange] { lv_bar_set_range(widget, paMinRange, paMaxRange); });
    return widget;
  }
  return nullptr;
}

lv_obj_t *LVGLExternalConnector::connectSlider(const std::string &paName,
                                              const std::string &paLabel,
                                              int32_t paMinRange,
                                              int32_t paMaxRange) {
  if (lv_obj_t *widget = findWidget(paName, &lv_slider_class)) {
    LVGLDriver::runLater([widget, paMinRange, paMaxRange] { lv_slider_set_range(widget, paMinRange, paMaxRange); });
    return widget;
  }
  return nullptr;
}

lv_obj_t *LVGLExternalConnector::connectSpinbox(const std::string &paName,
                                               const std::string &paLabel,
                                               int32_t paMinRange,
                                               int32_t paMaxRange) {
  if (lv_obj_t *widget = findWidget(paName, &lv_spinbox_class)) {
    LVGLDriver::runLater([widget, paMinRange, paMaxRange] { lv_spinbox_set_range(widget, paMinRange, paMaxRange); });
    return widget;
  }
  return nullptr;
}

lv_subject_t *LVGLExternalConnector::connectSubject(const std::string &paName) {
  return findSubject(paName);
}

lv_obj_t *LVGLExternalConnector::connectSwitch(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_switch_class);
}

lv_obj_t *LVGLExternalConnector::findWidget(const std::string &paName, const lv_obj_class_t *paClass) {
  lv_obj_t *obj = lv_obj_find_by_name(lv_screen_active(), paName.c_str());
  if (obj == nullptr) {
    DEVLOG_WARNING("[LVGLDeviceController] Cannot find widget with name '%s'\n", paName.c_str());
    return nullptr;
  }
  if (lv_obj_get_class(obj) != paClass) {
    DEVLOG_WARNING("[LVGLDeviceController] Unexpected widget with name '%s'\n", paName.c_str());
    return nullptr;
  }
  return obj;
}

lv_subject_t *LVGLExternalConnector::findSubject(const std::string &paName) {
  lv_subject_t *subject = lv_xml_get_subject(nullptr, paName.c_str());

  if (subject == nullptr) {
    DEVLOG_WARNING("[LVGLDeviceController] Cannot find subject '%s'\n", paName.c_str());
    return nullptr;
  }

  return subject;
}
