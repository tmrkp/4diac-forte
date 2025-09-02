#pragma once

#include "lvgl/lvgl.h"
#include <string>

class HMIGenerator {
  public:
    lv_obj_t *init();
    lv_obj_t *createBooleanIndicatorWidget(const std::string *paLabel) const;
    lv_obj_t *createButtonWidget(const std::string *paLabel) const;
    lv_obj_t *createCheckBoxWidget(const std::string *paLabel) const;
    lv_obj_t *createDropDownWidget(const std::string *paLabel, const std::string *paOption) const;
    lv_obj_t *createNumberWidget(const std::string *paLabel) const;
    lv_obj_t *createProgressBarWidget(const std::string *paLabel) const;
    lv_obj_t *createSliderWidget(const std::string *paLabel) const;
    lv_subject_t *createSubjectWidget(const std::string *paLabel) const;
    lv_obj_t *createSpinBoxWidget(const std::string *paLabel) const;
    lv_obj_t *createSwitchWidget(const std::string *paLabel) const;

  protected:
    lv_obj_t *mMain = nullptr;

    lv_obj_t *createWidgetWrapper() const;
    lv_obj_t *createWidgetWrapper(const std::string *paLabel) const;
};
