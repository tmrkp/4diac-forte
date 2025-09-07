#include "FORTE_HMISlider.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMISlider);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(MinRange);
USE_STRING_ID(MaxRange);
USE_STRING_ID(WidgetName);
USE_STRING_ID(ChangedIntegerInput);
USE_STRING_ID(ReleasedIntegerInput);
USE_STRING_ID(BOOL);
USE_STRING_ID(UDINT);
USE_STRING_ID(WSTRING);
USE_STRING_ID(STRING);
USE_STRING_ID(QO);
USE_STRING_ID(STATUS);
USE_STRING_ID(MAP);
USE_STRING_ID(MAPO);
USE_STRING_ID(IND);
USE_STRING_ID(IND);
USE_STRING_ID(HMIBusAdapter);
USE_STRING_ID(BusAdapterIn);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(Event);

DEFINE_FIRMWARE_FB(FORTE_HMISlider, STRID(HMISlider))

const CStringDictionary::TStringId FORTE_HMISlider::scmDataInputNames[] = {
    STRID(QI),
    STRID(Label),
    STRID(MinRange),
    STRID(MaxRange),
    STRID(WidgetName),
    STRID(ChangedIntegerInput),
    STRID(ReleasedIntegerInput),
};
const CStringDictionary::TStringId FORTE_HMISlider::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(UDINT), STRID(UDINT), STRID(STRING), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_HMISlider::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMISlider::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMISlider::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, scmWithListDelimiter};
const TForteInt16 FORTE_HMISlider::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMISlider::scmChangedIntegerInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMISlider::scmChangedIntegerInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMISlider::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMISlider::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMISlider::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMISlider::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMISlider::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMISlider::scmFBInterfaceSpec = {
    1,
    scmChangedIntegerInputNames,
    nullptr,
    scmEIWith,
    scmEIWithIndexes,
    2,
    scmEventOutputNames,
    nullptr,
    scmEOWith,
    scmEOWithIndexes,
    7,
    scmDataInputNames,
    scmDataInputTypeIds,
    2,
    scmDataOutputNames,
    scmDataOutputTypeIds,
    0,
    nullptr,
    2,
    scmAdapterInstances,
};

const TForteUInt8 FORTE_HMISlider::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMISlider::scmSlaveConfigurationIONum = 0;

FORTE_HMISlider::FORTE_HMISlider(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_MinRange(0_UDINT),
    var_MaxRange(100_UDINT),
    var_WidgetName(""_STRING),
    var_ChangedIntegerInput(""_STRING),
    var_ReleasedIntegerInput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_MinRange(nullptr),
    conn_MaxRange(nullptr),
    conn_WidgetName(nullptr),
    conn_ChangedIntegerInput(nullptr),
    conn_ReleasedIntegerInput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMISlider::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_MinRange = 0_UDINT;
  var_MaxRange = 100_UDINT;
  var_WidgetName = ""_STRING;
  var_ChangedIntegerInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMISlider::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(5, var_ChangedIntegerInput, conn_ChangedIntegerInput);
      readData(4, var_WidgetName, conn_WidgetName);
      readData(1, var_Label, conn_Label);
      readData(6, var_ReleasedIntegerInput, conn_ReleasedIntegerInput);
      readData(3, var_MaxRange, conn_MaxRange);
      readData(2, var_MinRange, conn_MinRange);
      break;
    }
    default: break;
  }
}

void FORTE_HMISlider::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMISlider::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_MinRange;
    case 3: return &var_MaxRange;
    case 4: return &var_WidgetName;
    case 5: return &var_ChangedIntegerInput;
    case 6: return &var_ReleasedIntegerInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMISlider::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMISlider::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMISlider::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_MinRange;
    case 3: return &conn_MaxRange;
    case 4: return &conn_WidgetName;
    case 5: return &conn_ChangedIntegerInput;
    case 6: return &conn_ReleasedIntegerInput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMISlider::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMISlider::initHandles() {
  lv_obj_t *widget =
      static_cast<HMIDeviceController &>(getController())
          .getConnector()
          .connectSlider(var_WidgetName.getStorage(), var_Label.getStorage(), static_cast<TForteUInt32>(var_MinRange),
                         static_cast<TForteUInt32>(var_MaxRange));

  if (widget) {
    HMIDeviceController::HMISliderValueHandleDescriptor changedDesc(
        var_ChangedIntegerInput.getStorage(), IOMapper::In, 0, CIEC_ANY::e_DWORD, widget, LV_EVENT_VALUE_CHANGED);
    initHandle(changedDesc);
    HMIDeviceController::HMISliderValueHandleDescriptor releasedDesc(
        var_ReleasedIntegerInput.getStorage(), IOMapper::In, 1, CIEC_ANY::e_DWORD, widget, LV_EVENT_RELEASED);
    initHandle(releasedDesc);
  }
}
