#include "HMIGenerator.h"

lv_obj_t *HMIGenerator::init() {
  mMain = lv_obj_create(nullptr);
  lv_obj_set_layout(mMain, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(mMain, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_style_pad_all(mMain, 20, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(mMain, 10, LV_STATE_DEFAULT);
  lv_screen_load(mMain);
  return mMain;
}

lv_obj_t *HMIGenerator::createWidgetWrapper() const {
  lv_obj_t *wrapper = lv_obj_create(mMain);
  lv_obj_set_size(wrapper, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_layout(wrapper, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(wrapper, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_style_flex_main_place(wrapper, LV_FLEX_ALIGN_CENTER, LV_STATE_DEFAULT);
  lv_obj_set_style_flex_cross_place(wrapper, LV_FLEX_ALIGN_CENTER, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(wrapper, 20, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(wrapper, 10, LV_STATE_DEFAULT);

  return wrapper;
}

lv_obj_t *HMIGenerator::createWidgetWrapper(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper();

  if (!paLabel->empty()) {
    lv_obj_t *label = lv_label_create(wrapper);
    lv_label_set_text(label, paLabel->c_str());
  }

  return wrapper;
}

lv_obj_t *HMIGenerator::createBooleanIndicatorWidget(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *led = lv_led_create(wrapper);
  return led;
}

lv_obj_t *HMIGenerator::createButtonWidget(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper();
  lv_obj_t *button = lv_button_create(wrapper);
  if (!paLabel->empty()) {
    lv_obj_t *label = lv_label_create(button);
    lv_label_set_text(label, paLabel->c_str());
  }
  return button;
}

lv_obj_t *HMIGenerator::createCheckBoxWidget(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *checkbox = lv_checkbox_create(wrapper);
  return checkbox;
}

lv_obj_t *HMIGenerator::createDropDownWidget(const std::string *paLabel, const std::string *paOptions) const {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *dropdown = lv_dropdown_create(wrapper);
  return dropdown;
}

lv_obj_t *HMIGenerator::createNumberWidget(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *number = lv_label_create(wrapper);
  return number;
}

lv_obj_t *HMIGenerator::createProgressBarWidget(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *bar = lv_bar_create(wrapper);
  return bar;
}

lv_obj_t *HMIGenerator::createSliderWidget(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *slider = lv_slider_create(wrapper);
  return slider;
}

lv_subject_t *HMIGenerator::createSubjectWidget(const std::string *paLabel) const {
  const std::string label = "Subject: " + *paLabel;
  lv_obj_t *wrapper = createWidgetWrapper(&label);
  lv_obj_t *number = lv_label_create(wrapper);
  lv_subject_t *subject = new lv_subject_t;
  lv_subject_init_int(subject, 0);
  lv_label_bind_text(number, subject, "%d");
  return subject;
}

lv_obj_t *HMIGenerator::createSwitchWidget(const std::string *paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *swtch = lv_switch_create(wrapper);
  return swtch;
}
