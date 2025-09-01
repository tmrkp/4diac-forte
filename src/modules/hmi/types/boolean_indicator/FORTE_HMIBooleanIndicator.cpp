#include "FORTE_HMIBooleanIndicator.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMIBooleanIndicator);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(BooleanOutput);
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

DEFINE_FIRMWARE_FB(FORTE_HMIBooleanIndicator, STRID(HMIBooleanIndicator))

const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmDataInputNames[] = {
    STRID(QI), STRID(Label), STRID(WidgetName), STRID(BooleanOutput)};
const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING),
                                                                                       STRID(STRING), STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIBooleanIndicator::scmEIWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_HMIBooleanIndicator::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMIBooleanIndicator::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMIBooleanIndicator::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMIBooleanIndicator::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMIBooleanIndicator::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMIBooleanIndicator::scmFBInterfaceSpec = {
    1,
    scmEventInputNames,
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

const TForteUInt8 FORTE_HMIBooleanIndicator::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMIBooleanIndicator::scmSlaveConfigurationIONum = 0;

FORTE_HMIBooleanIndicator::FORTE_HMIBooleanIndicator(const CStringDictionary::TStringId paInstanceNameId,
                                                     CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_BooleanOutput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_WidgetName(nullptr),
    conn_BooleanOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMIBooleanIndicator::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_BooleanOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIBooleanIndicator::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_BooleanOutput, conn_BooleanOutput);
      break;
    }
    default: break;
  }
}

void FORTE_HMIBooleanIndicator::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIBooleanIndicator::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_BooleanOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIBooleanIndicator::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIBooleanIndicator::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIBooleanIndicator::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_BooleanOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIBooleanIndicator::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMIBooleanIndicator::initHandles() {
  HMIDeviceController::HMIHandleDescriptor desc(var_BooleanOutput.getStorage(), 0,
                                                HMIDeviceController::BOOLEAN_INDICATOR, var_WidgetName.getStorage());
  initHandle(desc);
}
