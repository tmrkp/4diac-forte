#include "FORTE_HMIDropDown.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMIDropDown);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(Options);
USE_STRING_ID(WidgetName);
USE_STRING_ID(IntegerInput);
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

DEFINE_FIRMWARE_FB(FORTE_HMIDropDown, STRID(HMIDropDown))

const CStringDictionary::TStringId FORTE_HMIDropDown::scmDataInputNames[] = {STRID(QI), STRID(Label), STRID(Options),
                                                                             STRID(WidgetName), STRID(IntegerInput)};
const CStringDictionary::TStringId FORTE_HMIDropDown::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(STRING), STRID(STRING), STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMIDropDown::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIDropDown::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIDropDown::scmEIWith[] = {0, 1, 2, 3, 4, scmWithListDelimiter};
const TForteInt16 FORTE_HMIDropDown::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIDropDown::scmIntegerInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMIDropDown::scmIntegerInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMIDropDown::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMIDropDown::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMIDropDown::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMIDropDown::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMIDropDown::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMIDropDown::scmFBInterfaceSpec = {
    1,
    scmIntegerInputNames,
    nullptr,
    scmEIWith,
    scmEIWithIndexes,
    2,
    scmEventOutputNames,
    nullptr,
    scmEOWith,
    scmEOWithIndexes,
    5,
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

const TForteUInt8 FORTE_HMIDropDown::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMIDropDown::scmSlaveConfigurationIONum = 0;

FORTE_HMIDropDown::FORTE_HMIDropDown(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_Options(""_STRING),
    var_WidgetName(""_STRING),
    var_IntegerInput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_Options(nullptr),
    conn_WidgetName(nullptr),
    conn_IntegerInput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMIDropDown::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_Options = ""_STRING;
  var_WidgetName = ""_STRING;
  var_IntegerInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIDropDown::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_Options, conn_Options);
      readData(3, var_WidgetName, conn_WidgetName);
      readData(4, var_IntegerInput, conn_IntegerInput);
      break;
    }
    default: break;
  }
}

void FORTE_HMIDropDown::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIDropDown::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_Options;
    case 3: return &var_WidgetName;
    case 4: return &var_IntegerInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIDropDown::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIDropDown::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIDropDown::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_Options;
    case 3: return &conn_WidgetName;
    case 4: return &conn_IntegerInput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIDropDown::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMIDropDown::initHandles() {
  HMIDeviceController::HMIHandleDescriptor desc(var_IntegerInput.getStorage(), 0, HMIDeviceController::DROP_DOWN,
                                                var_WidgetName.getStorage(), var_Label.getStorage(),
                                                var_Options.getStorage());
  initHandle(desc);
}
