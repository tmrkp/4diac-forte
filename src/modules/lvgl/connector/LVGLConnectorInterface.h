#pragma once

#include <string>
#include "lvgl/lvgl.h"

class LVGLConnectorInterface {
  public:
    virtual ~LVGLConnectorInterface() = default;

    virtual void init() = 0;

    virtual lv_obj_t *connectButton(const std::string &paName, const std::string &paLabel) = 0;
    virtual lv_obj_t *connectChart(const std::string &paName,
                                   const std::string &paLabel,
                                   int32_t paMinYRange,
                                   int32_t paMaxYRange,
                                   uint32_t paPointCount) = 0;

    virtual lv_obj_t *connectCheckbox(const std::string &paName, const std::string &paLabel) = 0;
    virtual lv_obj_t *
    connectDropdown(const std::string &paName, const std::string &paLabel, const std::string &paOptions) = 0;
    virtual lv_obj_t *connectLED(const std::string &paName, const std::string &paLabel) = 0;
    virtual lv_obj_t *connectNumber(const std::string &paName, const std::string &paLabel) = 0;
    virtual lv_subject_t *connectObserver(const std::string &paName) = 0;
    virtual lv_obj_t *connectProgressbar(const std::string &paName,
                                         const std::string &paLabel,
                                         int32_t paMinRange,
                                         int32_t paMaxRange) = 0;
    virtual lv_obj_t *
    connectSlider(const std::string &paName, const std::string &paLabel, int32_t paMinRange, int32_t paMaxRange) = 0;
    virtual lv_obj_t *
    connectSpinbox(const std::string &paName, const std::string &paLabel, int32_t paMinRange, int32_t paMaxRange) = 0;
    virtual lv_subject_t *connectSubject(const std::string &paName) = 0;
    virtual lv_obj_t *connectSwitch(const std::string &paName, const std::string &paLabel) = 0;
};
