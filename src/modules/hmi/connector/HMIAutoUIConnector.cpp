#include "HMIAutoUIConnector.h"

void HMIAutoUIConnector::init() {
  mMain = lv_obj_create(nullptr);
  lv_obj_set_layout(mMain, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(mMain, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_style_pad_all(mMain, 20, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(mMain, 10, LV_STATE_DEFAULT);
  lv_screen_load(mMain);
}

lv_obj_t *HMIAutoUIConnector::connectButton(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper();
  lv_obj_t *button = lv_button_create(wrapper);
  if (!paLabel.empty()) {
    lv_obj_t *label = lv_label_create(button);
    lv_label_set_text(label, paLabel.c_str());
  }
  return button;
}

lv_obj_t *HMIAutoUIConnector::connectCheckbox(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *checkbox = lv_checkbox_create(wrapper);
  return checkbox;
}

lv_obj_t *HMIAutoUIConnector::connectDropdown(const std::string &paName,
                                              const std::string &paLabel,
                                              const std::string &paOptions) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *dropdown = lv_dropdown_create(wrapper);
  return dropdown;
}

lv_obj_t *HMIAutoUIConnector::connectLED(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *led = lv_led_create(wrapper);
  return led;
}

lv_obj_t *HMIAutoUIConnector::connectNumber(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *number = lv_label_create(wrapper);
  return number;
}

lv_subject_t *HMIAutoUIConnector::connectObserver(const std::string &paName) {
  // TODO
  return nullptr;
}

lv_obj_t *HMIAutoUIConnector::connectProgressbar(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *bar = lv_bar_create(wrapper);
  return bar;
}

lv_obj_t *HMIAutoUIConnector::connectSlider(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *slider = lv_slider_create(wrapper);
  return slider;
}

lv_obj_t *HMIAutoUIConnector::connectSpinbox(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *row = lv_obj_create(wrapper);
  lv_obj_set_size(row, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_set_layout(row, LV_LAYOUT_FLEX);
  lv_obj_set_style_flex_main_place(row, LV_FLEX_ALIGN_CENTER, LV_STATE_DEFAULT);
  lv_obj_set_style_flex_cross_place(row, LV_FLEX_ALIGN_CENTER, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(row, 0, LV_STATE_DEFAULT);
  lv_obj_t *inc_button = lv_button_create(row);
  lv_obj_set_size(inc_button, 28, 28);
  lv_obj_set_style_bg_image_src(inc_button, LV_SYMBOL_PLUS, LV_STATE_DEFAULT);
  lv_obj_t *spinbox = lv_spinbox_create(row);
  lv_spinbox_set_range(spinbox, 0, 100);
  lv_spinbox_set_digit_format(spinbox, 3, 0);
  lv_obj_t *dec_button = lv_button_create(row);
  lv_obj_set_size(dec_button, 28, 28);
  lv_obj_set_style_bg_image_src(dec_button, LV_SYMBOL_MINUS, LV_STATE_DEFAULT);
  lv_obj_add_event_cb(
      inc_button,
      [](lv_event_t *e) {
        auto *spinbox = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
        lv_spinbox_increment(spinbox);
      },
      LV_EVENT_CLICKED, spinbox);
  lv_obj_add_event_cb(
      dec_button,
      [](lv_event_t *e) {
        auto *spinbox = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
        lv_spinbox_decrement(spinbox);
      },
      LV_EVENT_CLICKED, spinbox);
  return spinbox;
}

lv_subject_t *HMIAutoUIConnector::connectSubject(const std::string &paName) {
  // TODO
  return nullptr;
}

lv_obj_t *HMIAutoUIConnector::connectSwitch(const std::string &paName, const std::string &paLabel) {
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *swtch = lv_switch_create(wrapper);
  return swtch;
}

lv_obj_t *HMIAutoUIConnector::createWidgetWrapper() const {
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

lv_obj_t *HMIAutoUIConnector::createWidgetWrapper(const std::string &paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper();

  if (!paLabel.empty()) {
    lv_obj_t *label = lv_label_create(wrapper);
    lv_label_set_text(label, paLabel.c_str());
  }

  return wrapper;
}
