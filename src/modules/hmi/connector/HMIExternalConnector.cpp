#include "HMIExternalConnector.h"

#include "HMIDriver.h"
#include "devlog.h"

void HMIExternalConnector::init() {
}

lv_obj_t *HMIExternalConnector::connectButton(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_button_class);
}

lv_obj_t *HMIExternalConnector::connectChart(const std::string &paName,
                                             const std::string &paLabel,
                                             uint32_t paMinYRange,
                                             uint32_t paMaxYRange,
                                             uint32_t paPointCount) {
  if (lv_obj_t *widget = findWidget(paName, &lv_chart_class)) {
    lv_chart_set_point_count(widget, paPointCount);
    if (std::in_range<int32_t>(paMinYRange) && std::in_range<int32_t>(paMaxYRange)) {
      HMIDriver::runLater([widget, paMinYRange, paMaxYRange] {
        lv_chart_set_axis_range(widget, LV_CHART_AXIS_PRIMARY_Y, static_cast<int32_t>(paMinYRange),
                                static_cast<int32_t>(paMaxYRange));
      });
    } else {
      // TODO: How to handle this?
    }
    return widget;
  }
  return nullptr;
}

lv_obj_t *HMIExternalConnector::connectCheckbox(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_checkbox_class);
}

lv_obj_t *HMIExternalConnector::connectDropdown(const std::string &paName,
                                                const std::string &paLabel,
                                                const std::string &paOptions) {
  return findWidget(paName, &lv_dropdown_class);
}

lv_obj_t *HMIExternalConnector::connectLED(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_led_class);
}

lv_obj_t *HMIExternalConnector::connectNumber(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_label_class);
}

lv_subject_t *HMIExternalConnector::connectObserver(const std::string &paName) {
  return findSubject(paName);
}

lv_obj_t *HMIExternalConnector::connectProgressbar(const std::string &paName,
                                                   const std::string &paLabel,
                                                   uint32_t paMinRange,
                                                   uint32_t paMaxRange) {
  if (lv_obj_t *widget = findWidget(paName, &lv_bar_class)) {
    if (std::in_range<int32_t>(paMinRange) && std::in_range<int32_t>(paMaxRange)) {
      HMIDriver::runLater([widget, paMinRange, paMaxRange] {
        lv_bar_set_range(widget, static_cast<int32_t>(paMinRange), static_cast<int32_t>(paMaxRange));
      });
    } else {
      // TODO: How to handle this?
    }
    return widget;
  }
  return nullptr;
}

lv_obj_t *HMIExternalConnector::connectSlider(const std::string &paName,
                                              const std::string &paLabel,
                                              uint32_t paMinRange,
                                              uint32_t paMaxRange) {
  if (lv_obj_t *widget = findWidget(paName, &lv_slider_class)) {
    if (std::in_range<int32_t>(paMinRange) && std::in_range<int32_t>(paMaxRange)) {
      HMIDriver::runLater([widget, paMinRange, paMaxRange] {
        lv_slider_set_range(widget, static_cast<int32_t>(paMinRange), static_cast<int32_t>(paMaxRange));
      });
    } else {
      // TODO: How to handle this?
    }
    return widget;
  }
  return nullptr;
}

lv_obj_t *HMIExternalConnector::connectSpinbox(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_spinbox_class);
}

lv_subject_t *HMIExternalConnector::connectSubject(const std::string &paName) {
  return findSubject(paName);
}

lv_obj_t *HMIExternalConnector::connectSwitch(const std::string &paName, const std::string &paLabel) {
  return findWidget(paName, &lv_switch_class);
}

lv_obj_t *HMIExternalConnector::findWidget(const std::string &paName, const lv_obj_class_t *paClass) {
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

lv_subject_t *HMIExternalConnector::findSubject(const std::string &paName) {
  lv_subject_t *subject = lv_xml_get_subject(nullptr, paName.c_str());

  if (subject == nullptr) {
    DEVLOG_WARNING("[HMIDeviceController] Cannot find subject '%s'\n", paName.c_str());
    return nullptr;
  }

  return subject;
}
