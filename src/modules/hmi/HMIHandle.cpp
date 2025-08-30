#include "HMIHandle.h"

#include "lvgl/lvgl.h"
#include "forte_word.h"
#include "forte_dword.h"
#include "startup.h"

HMIHandle::HMIHandle(HMIDeviceController *paController,
                     CIEC_ANY::EDataTypeID paType,
                     IOMapper::Direction paDirection,
                     TargetType paTargetType,
                     std::string const &paName) :
    IOHandle(paController, paDirection, paType),
    mTargetType(paTargetType),
    mName(paName) {
  if (paDirection == IOMapper::In) {
    lv_obj_t *obj = lv_obj_find_by_name(lv_screen_active(), mName.c_str());

    if (obj == nullptr) {
      DEVLOG_WARNING("[HMIHandle] Cannot find widget '%s'\n", mName.c_str());
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
    } else if (lv_obj_get_class(obj) == &lv_slider_class) {
      lv_obj_add_event_cb(
          obj,
          [](lv_event_t *e) {
            const auto handle = static_cast<HMIHandle *>(lv_event_get_user_data(e));
            handle->mHasChanged = true;
          },
          LV_EVENT_VALUE_CHANGED, this);
    } else if (lv_obj_get_class(obj) == &lv_switch_class) {
      lv_obj_add_event_cb(
          obj,
          [](lv_event_t *e) {
            const auto handle = static_cast<HMIHandle *>(lv_event_get_user_data(e));
            handle->mHasChanged = true;
          },
          LV_EVENT_VALUE_CHANGED, this);
    } else if (lv_obj_get_class(obj) == &lv_dropdown_class) {
      lv_obj_add_event_cb(
          obj,
          [](lv_event_t *e) {
            const auto handle = static_cast<HMIHandle *>(lv_event_get_user_data(e));
            handle->mHasChanged = true;
          },
          LV_EVENT_VALUE_CHANGED, this);
    } else {
      DEVLOG_WARNING("[HMIHandle] Widget type not supported '%s'\n", mName.c_str());
    }
  }
}

void HMIHandle::set(const CIEC_ANY &paState) {
  if (mTargetType == TargetType::WIDGET) {
    lv_obj_t *obj = lv_obj_find_by_name(lv_screen_active(), mName.c_str());

    if (obj == nullptr) {
      DEVLOG_WARNING("[HMIHandle] Cannot find widget '%s'\n", mName.c_str());
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
    } else if (lv_obj_get_class(obj) == &lv_label_class) {
      TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
      runLater([dword, obj]() { lv_label_set_text_fmt(obj, "%d", dword); });
    } else if (lv_obj_get_class(obj) == &lv_bar_class) {
      TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
      runLater([dword, obj]() { lv_bar_set_value(obj, dword, false); });
    } else {
      DEVLOG_WARNING("[HMIHandle] Widget type not supported '%s'\n", mName.c_str());
    }
  } else if (mTargetType == TargetType::SUBJECT) {
    lv_subject_t *subject = lv_xml_get_subject(nullptr, mName.c_str());

    if (subject == nullptr) {
      DEVLOG_WARNING("[HMIHandle] Cannot find subject '%s'\n", mName.c_str());
      return;
    }

    TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
    runLater([subject, dword]() { lv_subject_set_int(subject, dword); });
  }
}

void HMIHandle::get(CIEC_ANY &paState) {
  lv_obj_t *obj = lv_obj_find_by_name(lv_screen_active(), mName.c_str());

  if (obj == nullptr) {
    DEVLOG_WARNING("[HMIHandle] Cannot find widget '%s'\n", mName.c_str());
    return;
  }

  if (lv_obj_get_class(obj) == &lv_slider_class) {
    int32_t value = lv_slider_get_value(obj);

    switch (mType) {
      case CIEC_ANY::e_DWORD: {
        static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(value);
        break;
      }
      default: {
        DEVLOG_WARNING("[HMIHandle] Unexpected type '%d'\n", mType);
        break;
      }
    }
  } else if (lv_obj_get_class(obj) == &lv_switch_class) {
    bool checked = lv_obj_has_state(obj, LV_STATE_CHECKED);

    switch (mType) {
      case CIEC_ANY::e_BOOL: {
        static_cast<CIEC_BOOL &>(paState) = CIEC_BOOL(checked);
        break;
      }
      default: {
        DEVLOG_WARNING("[HMIHandle] Unexpected type '%d'\n", mType);
        break;
      }
    }
  } else if (lv_obj_get_class(obj) == &lv_dropdown_class) {
    uint32_t value = lv_dropdown_get_selected(obj);

    switch (mType) {
      case CIEC_ANY::e_DWORD: {
        static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(value);
        break;
      }
      default: {
        DEVLOG_WARNING("[HMIHandle] Unexpected type '%d'\n", mType);
        break;
      }
    }
  }
}

bool HMIHandle::hasChanged() {
  if (mHasChanged) {
    mHasChanged = false;
    return true;
  }
  return false;
}
