#include "FORTE_HMISwitch.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMISwitch);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(BooleanInput);
USE_STRING_ID(BOOL);
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

DEFINE_FIRMWARE_FB(FORTE_HMISwitch, STRID(HMISwitch))

const CStringDictionary::TStringId FORTE_HMISwitch::scmDataInputNames[] = {STRID(QI), STRID(Label), STRID(WidgetName),
                                                                           STRID(BooleanInput)};
const CStringDictionary::TStringId FORTE_HMISwitch::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING), STRID(STRING),
                                                                             STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMISwitch::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMISwitch::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMISwitch::scmEIWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_HMISwitch::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMISwitch::scmBooleanInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMISwitch::scmBooleanInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMISwitch::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMISwitch::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMISwitch::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMISwitch::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMISwitch::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMISwitch::scmFBInterfaceSpec = {
    1,
    scmBooleanInputNames,
    nullptr,
    scmEIWith,
    scmEIWithIndexes,
    2,
    scmEventOutputNames,
    nullptr,
    scmEOWith,
    scmEOWithIndexes,
    4,
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

const TForteUInt8 FORTE_HMISwitch::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMISwitch::scmSlaveConfigurationIONum = 0;

FORTE_HMISwitch::FORTE_HMISwitch(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_BooleanInput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_WidgetName(nullptr),
    conn_BooleanInput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMISwitch::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_BooleanInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMISwitch::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_BooleanInput, conn_BooleanInput);
      break;
    }
    default: break;
  }
}

void FORTE_HMISwitch::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMISwitch::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_BooleanInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMISwitch::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMISwitch::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMISwitch::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_BooleanInput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMISwitch::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMISwitch::initHandles() {
  lv_obj_t *widget = static_cast<HMIDeviceController &>(getController())
                         .getConnector()
                         .connectSwitch(var_WidgetName.getStorage(), var_Label.getStorage());

  if (!widget) {
    return;
  }

  HMIDeviceController::HMIWidgetStateHandleDescriptor desc(var_BooleanInput.getStorage(), IOMapper::In, 0,
                                                           CIEC_ANY::e_BOOL, widget, LV_STATE_CHECKED,
                                                           LV_EVENT_VALUE_CHANGED);
  initHandle(desc);
}
