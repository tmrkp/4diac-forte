#include "FORTE_HMILED.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMILED);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(BooleanOutput);
USE_STRING_ID(ByteOutput);
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

DEFINE_FIRMWARE_FB(FORTE_HMILED, STRID(HMILED))

const CStringDictionary::TStringId FORTE_HMILED::scmDataInputNames[] = {STRID(QI), STRID(Label), STRID(WidgetName),
                                                                        STRID(BooleanOutput), STRID(ByteOutput)};
const CStringDictionary::TStringId FORTE_HMILED::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING), STRID(STRING),
                                                                          STRID(STRING), STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMILED::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMILED::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMILED::scmEIWith[] = {0, 1, 2, 3, 4, scmWithListDelimiter};
const TForteInt16 FORTE_HMILED::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMILED::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMILED::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMILED::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMILED::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMILED::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMILED::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMILED::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMILED::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_HMILED::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMILED::scmSlaveConfigurationIONum = 0;

FORTE_HMILED::FORTE_HMILED(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_BooleanOutput(""_STRING),
    var_ByteOutput(""_STRING),
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
    conn_ByteOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMILED::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_BooleanOutput = ""_STRING;
  var_ByteOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMILED::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_BooleanOutput, conn_BooleanOutput);
      readData(4, var_ByteOutput, conn_ByteOutput);
      break;
    }
    default: break;
  }
}

void FORTE_HMILED::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMILED::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_BooleanOutput;
    case 4: return &var_ByteOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMILED::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMILED::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMILED::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_BooleanOutput;
    case 4: return &conn_ByteOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMILED::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMILED::initHandles() {
  HMIDeviceController::HMILEDBrightnessHandleDescriptor boolDesc(var_BooleanOutput.getStorage(), 0, CIEC_ANY::e_BOOL,
                                                                 var_WidgetName.getStorage());
  initHandle(boolDesc);
  HMIDeviceController::HMILEDBrightnessHandleDescriptor byteDesc(var_BooleanOutput.getStorage(), 1, CIEC_ANY::e_BYTE,
                                                                 var_WidgetName.getStorage());
  initHandle(byteDesc);
}
