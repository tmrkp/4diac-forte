#include "LVGLAutoUIConnector.h"

#include "LVGLDriver.h"

void LVGLAutoUIConnector::init() {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  mMain = lv_obj_create(nullptr);
  lv_obj_set_layout(mMain, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(mMain, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_style_pad_all(mMain, 20, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(mMain, 10, LV_STATE_DEFAULT);
  lv_screen_load(mMain);
}

lv_obj_t *LVGLAutoUIConnector::connectButton(const std::string &paName, const std::string &paLabel) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper();
  lv_obj_t *button = lv_button_create(wrapper);
  if (!paLabel.empty()) {
    lv_obj_t *label = lv_label_create(button);
    lv_label_set_text(label, paLabel.c_str());
  }
  return button;
}

lv_obj_t *LVGLAutoUIConnector::connectChart(const std::string &paName,
                                           const std::string &paLabel,
                                           int32_t paMinYRange,
                                           int32_t paMaxYRange,
                                           uint32_t paPointCount) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *chart = lv_chart_create(wrapper);
  lv_obj_set_size(chart, 200, 150);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
  lv_chart_set_point_count(chart, paPointCount);
  lv_chart_set_axis_range(chart, LV_CHART_AXIS_PRIMARY_Y, paMinYRange, paMaxYRange);
  return chart;
}

lv_obj_t *LVGLAutoUIConnector::connectCheckbox(const std::string &paName, const std::string &paLabel) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *checkbox = lv_checkbox_create(wrapper);
  return checkbox;
}

lv_obj_t *LVGLAutoUIConnector::connectDropdown(const std::string &paName,
                                              const std::string &paLabel,
                                              const std::string &paOptions) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *dropdown = lv_dropdown_create(wrapper);
  lv_dropdown_set_options(dropdown, replaceEscapedNewline(paOptions).c_str());
  return dropdown;
}

lv_obj_t *LVGLAutoUIConnector::connectLED(const std::string &paName, const std::string &paLabel) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *led = lv_led_create(wrapper);
  return led;
}

lv_obj_t *LVGLAutoUIConnector::connectNumber(const std::string &paName, const std::string &paLabel) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *number = lv_label_create(wrapper);
  return number;
}

lv_subject_t *LVGLAutoUIConnector::connectObserver(const std::string &paName) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  // TODO
  return nullptr;
}

lv_obj_t *LVGLAutoUIConnector::connectProgressbar(const std::string &paName,
                                                 const std::string &paLabel,
                                                 int32_t paMinRange,
                                                 int32_t paMaxRange) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *bar = lv_bar_create(wrapper);
  lv_bar_set_range(bar, paMinRange, paMaxRange);
  return bar;
}

lv_obj_t *LVGLAutoUIConnector::connectSlider(const std::string &paName,
                                            const std::string &paLabel,
                                            int32_t paMinRange,
                                            int32_t paMaxRange) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *slider = lv_slider_create(wrapper);
  lv_slider_set_range(slider, paMinRange, paMaxRange);
  return slider;
}

lv_obj_t *LVGLAutoUIConnector::connectSpinbox(const std::string &paName,
                                             const std::string &paLabel,
                                             int32_t paMinRange,
                                             int32_t paMaxRange) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
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
  lv_spinbox_set_range(spinbox, paMinRange, paMaxRange);
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

lv_subject_t *LVGLAutoUIConnector::connectSubject(const std::string &paName) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  // TODO
  return nullptr;
}

lv_obj_t *LVGLAutoUIConnector::connectSwitch(const std::string &paName, const std::string &paLabel) {
  CCriticalRegion criticalRegion(LVGLDriver::timerMutex);
  lv_obj_t *wrapper = createWidgetWrapper(paLabel);
  lv_obj_t *swtch = lv_switch_create(wrapper);
  return swtch;
}

lv_obj_t *LVGLAutoUIConnector::createWidgetWrapper() const {
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

lv_obj_t *LVGLAutoUIConnector::createWidgetWrapper(const std::string &paLabel) const {
  lv_obj_t *wrapper = createWidgetWrapper();

  if (!paLabel.empty()) {
    lv_obj_t *label = lv_label_create(wrapper);
    lv_label_set_text(label, paLabel.c_str());
  }

  return wrapper;
}

std::string LVGLAutoUIConnector::replaceEscapedNewline(const std::string &input) {
  std::string result = input;
  std::string::size_type pos = 0;

  while ((pos = result.find("\\n", pos)) != std::string::npos) {
    result.replace(pos, 2, "\n");
    ++pos;
  }

  return result;
}
