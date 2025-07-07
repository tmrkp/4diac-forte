#include "HMIHandle.h"

#include "lvgl/lvgl.h"

extern void runLater(std::function<void()>);

HMIHandle::HMIHandle(HMIDeviceController *paController,
                     CIEC_ANY::EDataTypeID paType,
                     IOMapper::Direction paDirection,
                     std::string const &paWidgetName) :
    IOHandle(paController, paDirection, paType),
    mWidgetName(paWidgetName) {
  if (paDirection == IOMapper::In) {
    lv_obj_t *obj = lv_obj_find_by_name(lv_screen_active(), mWidgetName.c_str());

    if (obj == nullptr) {
      DEVLOG_WARNING("[HMIHandle] Cannot find widget '%s'\n", mWidgetName.c_str());
      return;
    }

    if (lv_obj_get_class(obj) == &lv_button_class) {
      lv_obj_add_event_cb(
          obj,
          [](lv_event_t *e) {
            const auto handle = static_cast<HMIHandle *>(lv_event_get_user_data(e));
            handle->mHasChanged = true;
          },
          LV_EVENT_CLICKED, this);
    } else {
      DEVLOG_WARNING("[HMIHandle] Widget type not supported '%s'\n", mWidgetName.c_str());
    }
  }
}

void HMIHandle::set(const CIEC_ANY &paState) {
  lv_obj_t *obj = lv_obj_find_by_name(lv_screen_active(), mWidgetName.c_str());

  if (obj == nullptr) {
    DEVLOG_WARNING("[HMIHandle] Cannot find widget '%s'\n", mWidgetName.c_str());
    return;
  }

  if (lv_obj_get_class(obj) == &lv_led_class) {
    bool on = static_cast<const CIEC_BOOL &>(paState);
    runLater([on, obj]() {
      if (on == true) {
        lv_led_on(obj);
      } else {
        lv_led_off(obj);
      }
    });
  } else if (lv_obj_get_class(obj) == &lv_checkbox_class) {
    bool checked = static_cast<const CIEC_BOOL &>(paState);
    runLater([checked, obj]() {
      if (checked == true) {
        lv_obj_add_state(obj, LV_STATE_CHECKED);
      } else {
        lv_obj_remove_state(obj, LV_STATE_CHECKED);
      }
    });
  } else {
    DEVLOG_WARNING("[HMIHandle] Widget type not supported '%s'\n", mWidgetName.c_str());
  }
}

void HMIHandle::get(CIEC_ANY &paState) {
}

bool HMIHandle::hasChanged() {
  if (mHasChanged) {
    mHasChanged = false;
    return true;
  }
  return false;
}
