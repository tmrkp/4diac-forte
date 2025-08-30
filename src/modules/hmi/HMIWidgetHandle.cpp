#include "HMIWidgetHandle.h"

#include "forte_word.h"
#include "forte_dword.h"
#include "startup.h"

HMIWidgetHandle::HMIWidgetHandle(HMIDeviceController *paController,
                                 CIEC_ANY::EDataTypeID paType,
                                 IOMapper::Direction paDirection,
                                 std::string const &paName) :
    IOHandle(paController, paDirection, paType),
    mName(paName) {

  mObj = lv_obj_find_by_name(lv_screen_active(), mName.c_str());

  if (mObj == nullptr) {
    DEVLOG_WARNING("[HMIWidgetHandle] Cannot find widget '%s'\n", mName.c_str());
    return;
  }

  if (paDirection == IOMapper::In) {
    if (lv_obj_get_class(mObj) == &lv_button_class) {
      lv_obj_add_event_cb(mObj, changeHandler, LV_EVENT_CLICKED, this);
    } else if (lv_obj_get_class(mObj) == &lv_slider_class) {
      lv_obj_add_event_cb(mObj, changeHandler, LV_EVENT_VALUE_CHANGED, this);
    } else if (lv_obj_get_class(mObj) == &lv_switch_class) {
      lv_obj_add_event_cb(mObj, changeHandler, LV_EVENT_VALUE_CHANGED, this);
    } else if (lv_obj_get_class(mObj) == &lv_dropdown_class) {
      lv_obj_add_event_cb(mObj, changeHandler, LV_EVENT_VALUE_CHANGED, this);
    } else {
      DEVLOG_WARNING("[HMIWidgetHandle] Widget type not supported '%s'\n", mName.c_str());
    }
  }
}

void HMIWidgetHandle::set(const CIEC_ANY &paState) {
  if (mObj == nullptr) {
    return;
  }

  if (lv_obj_get_class(mObj) == &lv_led_class) {
    bool on = static_cast<const CIEC_BOOL &>(paState);
    runLater([this, on] {
      if (on == true) {
        lv_led_on(mObj);
      } else {
        lv_led_off(mObj);
      }
    });
  } else if (lv_obj_get_class(mObj) == &lv_checkbox_class) {
    bool checked = static_cast<const CIEC_BOOL &>(paState);
    runLater([this, checked] {
      if (checked == true) {
        lv_obj_add_state(mObj, LV_STATE_CHECKED);
      } else {
        lv_obj_remove_state(mObj, LV_STATE_CHECKED);
      }
    });
  } else if (lv_obj_get_class(mObj) == &lv_label_class) {
    TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
    runLater([this, dword] { lv_label_set_text_fmt(mObj, "%d", dword); });
  } else if (lv_obj_get_class(mObj) == &lv_bar_class) {
    int32_t dword = static_cast<const CIEC_DWORD &>(paState);
    runLater([this, dword] { lv_bar_set_value(mObj, dword, false); });
  } else {
    DEVLOG_WARNING("[HMIWidgetHandle] Widget type not supported '%s'\n", mName.c_str());
  }
}

void HMIWidgetHandle::get(CIEC_ANY &paState) {
  if (mObj == nullptr) {
    return;
  }

  if (lv_obj_get_class(mObj) == &lv_slider_class) {
    int32_t value = lv_slider_get_value(mObj);

    switch (mType) {
      case CIEC_ANY::e_DWORD: {
        static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(value);
        break;
      }
      default: {
        DEVLOG_WARNING("[HMIWidgetHandle] Unexpected type '%d'\n", mType);
        break;
      }
    }
  } else if (lv_obj_get_class(mObj) == &lv_switch_class) {
    bool checked = lv_obj_has_state(mObj, LV_STATE_CHECKED);

    switch (mType) {
      case CIEC_ANY::e_BOOL: {
        static_cast<CIEC_BOOL &>(paState) = CIEC_BOOL(checked);
        break;
      }
      default: {
        DEVLOG_WARNING("[HMIWidgetHandle] Unexpected type '%d'\n", mType);
        break;
      }
    }
  } else if (lv_obj_get_class(mObj) == &lv_dropdown_class) {
    uint32_t value = lv_dropdown_get_selected(mObj);

    switch (mType) {
      case CIEC_ANY::e_DWORD: {
        static_cast<CIEC_DWORD &>(paState) = CIEC_DWORD(value);
        break;
      }
      default: {
        DEVLOG_WARNING("[HMIWidgetHandle] Unexpected type '%d'\n", mType);
        break;
      }
    }
  }
}

bool HMIWidgetHandle::hasChanged() {
  if (mHasChanged) {
    mHasChanged = false;
    return true;
  }
  return false;
}

void HMIWidgetHandle::changeHandler(lv_event_t *e) {
  const auto handle = static_cast<HMIWidgetHandle *>(lv_event_get_user_data(e));
  handle->mHasChanged = true;
}
