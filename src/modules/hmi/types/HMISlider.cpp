#include "HMISlider.h"

#include "../HMIDeviceController.h"

USE_STRING_ID(HMISlider);
USE_STRING_ID(QI);
USE_STRING_ID(WidgetName);
USE_STRING_ID(ValueParam);
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

DEFINE_FIRMWARE_FB(FORTE_HMISlider, STRID(HMISlider))

const CStringDictionary::TStringId FORTE_HMISlider::scmDataInputNames[] = {STRID(QI), STRID(WidgetName),
                                                                           STRID(ValueParam)};
const CStringDictionary::TStringId FORTE_HMISlider::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING), STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMISlider::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMISlider::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMISlider::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_HMISlider::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMISlider::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMISlider::scmEventInputTypeIds[] = {STRID(Event)};
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
    scmEventInputNames,
    nullptr,
    scmEIWith,
    scmEIWithIndexes,
    2,
    scmEventOutputNames,
    nullptr,
    scmEOWith,
    scmEOWithIndexes,
    3,
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
    var_WidgetName(""_STRING),
    var_ValueParam(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_WidgetName(nullptr),
    conn_ValueParam(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMISlider::setInitialValues() {
  var_QI = 0_BOOL;
  var_WidgetName = ""_STRING;
  var_ValueParam = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMISlider::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_WidgetName, conn_WidgetName);
      readData(2, var_ValueParam, conn_ValueParam);
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
    case 1: return &var_WidgetName;
    case 2: return &var_ValueParam;
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
    case 1: return &conn_WidgetName;
    case 2: return &conn_ValueParam;
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
  HMIDeviceController::HMIHandleDescriptor desc(var_ValueParam.getStorage(), IOMapper::In, 0, CIEC_ANY::e_DWORD,
                                                var_WidgetName.getStorage());
  initHandle(desc);
}
