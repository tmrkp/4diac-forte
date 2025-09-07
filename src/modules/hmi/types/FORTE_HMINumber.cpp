#include "FORTE_HMINumber.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMINumber);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(IntegerOutput);
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

DEFINE_FIRMWARE_FB(FORTE_HMINumber, STRID(HMINumber))

const CStringDictionary::TStringId FORTE_HMINumber::scmDataInputNames[] = {STRID(QI), STRID(Label), STRID(WidgetName),
                                                                           STRID(IntegerOutput)};
const CStringDictionary::TStringId FORTE_HMINumber::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING), STRID(STRING),
                                                                             STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMINumber::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMINumber::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMINumber::scmEIWith[] = {0, 1, 2, 3, scmWithListDelimiter};
const TForteInt16 FORTE_HMINumber::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMINumber::scmIntegerOutputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMINumber::scmIntegerOutputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMINumber::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMINumber::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMINumber::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMINumber::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMINumber::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMINumber::scmFBInterfaceSpec = {
    1,
    scmIntegerOutputNames,
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

const TForteUInt8 FORTE_HMINumber::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMINumber::scmSlaveConfigurationIONum = 0;

FORTE_HMINumber::FORTE_HMINumber(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_IntegerOutput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_WidgetName(nullptr),
    conn_IntegerOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMINumber::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_IntegerOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMINumber::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_IntegerOutput, conn_IntegerOutput);
      break;
    }
    default: break;
  }
}

void FORTE_HMINumber::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMINumber::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_IntegerOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMINumber::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMINumber::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMINumber::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_IntegerOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMINumber::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMINumber::initHandles() {
  lv_obj_t *widget = static_cast<HMIDeviceController &>(getController())
                         .getConnector()
                         .connectNumber(var_WidgetName.getStorage(), var_Label.getStorage());

  if (!widget) {
    // TODO: set status
    return;
  }

  HMIDeviceController::HMINumberTextHandleDescriptor desc(var_IntegerOutput.getStorage(), IOMapper::Out, 0,
                                                          CIEC_ANY::e_DWORD, widget);
  initHandle(desc);
}
