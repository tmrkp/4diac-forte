#pragma once

#include "HMIConnectorInterface.h"

class HMIAutoUIConnector : public HMIConnectorInterface {
  public:
    void init() override;
    lv_obj_t *connectButton(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *connectCheckbox(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *
    connectDropdown(const std::string &paName, const std::string &paLabel, const std::string &paOptions) override;
    lv_obj_t *connectLED(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *connectNumber(const std::string &paName, const std::string &paLabel) override;
    lv_subject_t *connectObserver(const std::string &paName) override;
    lv_obj_t *connectProgressbar(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *connectSlider(const std::string &paName, const std::string &paLabel) override;
    lv_obj_t *connectSpinbox(const std::string &paName, const std::string &paLabel) override;
    lv_subject_t *connectSubject(const std::string &paName) override;
    lv_obj_t *connectSwitch(const std::string &paName, const std::string &paLabel) override;

  protected:
    lv_obj_t *mMain = nullptr;

    lv_obj_t *createWidgetWrapper() const;
    lv_obj_t *createWidgetWrapper(const std::string &paLabel) const;
};
