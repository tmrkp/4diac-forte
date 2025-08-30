#include "HMISubjectHandle.h"

#include "lvgl/lvgl.h"
#include "startup.h"
#include "forte_dword.h"

HMISubjectHandle::HMISubjectHandle(HMIDeviceController *paController,
                                   CIEC_ANY::EDataTypeID paType,
                                   IOMapper::Direction paDirection,
                                   std::string const &paName) :
    IOHandle(paController, paDirection, paType),
    mName(paName) {
  mSubject = lv_xml_get_subject(nullptr, mName.c_str());

  if (mSubject == nullptr) {
    DEVLOG_WARNING("[HMISubjectHandle] Cannot find subject '%s'\n", mName.c_str());
    return;
  }
}

void HMISubjectHandle::get(CIEC_ANY &) {
}

void HMISubjectHandle::set(const CIEC_ANY &paState) {
  if (mSubject == nullptr) {
    return;
  }

  int32_t dword = static_cast<const CIEC_DWORD &>(paState);
  runLater([this, dword] { lv_subject_set_int(mSubject, dword); });
}

bool HMISubjectHandle::hasChanged() {
  return false;
}
