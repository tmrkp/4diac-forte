#include "HMILightIndicator.h"

#include "../HMIDeviceController.h"

USE_STRING_ID(HMILightIndicator);
USE_STRING_ID(QI);
USE_STRING_ID(LABEL);
USE_STRING_ID(WIDGETNAME);
USE_STRING_ID(BoolOutput);
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

DEFINE_FIRMWARE_FB(FORTE_HMILightIndicator, STRID(HMILightIndicator))

const CStringDictionary::TStringId FORTE_HMILightIndicator::scmDataInputNames[] = {
    STRID(QI),
    STRID(LABEL),
    STRID(WIDGETNAME),
    STRID(BoolOutput),
};
const CStringDictionary::TStringId FORTE_HMILightIndicator::scmDataInputTypeIds[] = {
    STRID(BOOL),
    STRID(WSTRING),
    STRID(WSTRING),
    STRID(STRING),
};
const CStringDictionary::TStringId FORTE_HMILightIndicator::scmDataOutputNames[] = {
    STRID(QO),
    STRID(STATUS),
};
const CStringDictionary::TStringId FORTE_HMILightIndicator::scmDataOutputTypeIds[] = {
    STRID(BOOL),
    STRID(WSTRING),
};
const TDataIOID FORTE_HMILightIndicator::scmEIWith[] = {0, 1, 3, 2, scmWithListDelimiter};
const TForteInt16 FORTE_HMILightIndicator::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMILightIndicator::scmEventInputNames[] = {
    STRID(MAP),
};
const CStringDictionary::TStringId FORTE_HMILightIndicator::scmEventInputTypeIds[] = {
    STRID(Event),
};
const TDataIOID FORTE_HMILightIndicator::scmEOWith[] = {0, scmWithListDelimiter, 1, 0, scmWithListDelimiter};
const TForteInt16 FORTE_HMILightIndicator::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMILightIndicator::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMILightIndicator::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMILightIndicator::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMILightIndicator::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_HMILightIndicator::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMILightIndicator::scmSlaveConfigurationIONum = 0;

FORTE_HMILightIndicator::FORTE_HMILightIndicator(const CStringDictionary::TStringId paInstanceNameId,
                                                 CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_LABEL(u""_WSTRING),
    var_WIDGETNAME(u""_WSTRING),
    var_BoolOutput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_LABEL(nullptr),
    conn_BoolOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMILightIndicator::setInitialValues() {
  var_QI = 0_BOOL;
  var_LABEL = u""_WSTRING;
  var_WIDGETNAME = u""_WSTRING;
  var_BoolOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMILightIndicator::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_LABEL, conn_LABEL);
      readData(2, var_BoolOutput, conn_BoolOutput);
      break;
    }
    default: break;
  }
}

void FORTE_HMILightIndicator::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMILightIndicator::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_LABEL;
    case 2: return &var_BoolOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMILightIndicator::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMILightIndicator::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMILightIndicator::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_LABEL;
    case 2: return &conn_BoolOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMILightIndicator::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMILightIndicator::initHandles() {
  HMIDeviceController::HMIHandleDescriptor desc(var_BoolOutput.getStorage(), IOMapper::Out, 0, CIEC_ANY::e_BOOL);
  initHandle(desc);
}
