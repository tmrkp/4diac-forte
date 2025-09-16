#pragma once

#include "LVGLConnectorInterface.h"

class LVGLExternalConnector : public LVGLConnectorInterface {
  public:
    void init() override;
    lv_obj_t *connectButton(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *connectChart(const std::string &paName,
                           const std::string &paLabel,
                           int32_t paMinYRange,
                           int32_t paMaxYRange,
                           uint32_t paPointCount) override;
    lv_obj_t *connectCheckbox(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *
    connectDropdown(const std::string &paName, const std::string &paLabel, const std::string &paOptions) override;
    lv_obj_t *connectLED(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *connectNumber(const std::string &paName, const std::string &paLabel) override;
    lv_subject_t *connectObserver(const std::string &paName) override;
    lv_obj_t *connectProgressbar(const std::string &paName,
                                 const std::string &paLabel,
                                 int32_t paMinRange,
                                 int32_t paMaxRange) override;
    lv_obj_t *connectSlider(const std::string &paName,
                            const std::string &paLabel,
                            int32_t paMinRange,
                            int32_t paMaxRange) override;
    lv_obj_t *connectSpinbox(const std::string &paName,
                             const std::string &paLabel,
                             int32_t paMinRange,
                             int32_t paMaxRange) override;
    lv_subject_t *connectSubject(const std::string &paName) override;
    lv_obj_t *connectSwitch(const std::string &paName, const std::string &paLabel) override;

  private:
    static lv_obj_t *findWidget(const std::string &paName, const lv_obj_class_t *paClass);
    static lv_subject_t *findSubject(const std::string &paName);
};
