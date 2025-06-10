#include "HMIButton.h"

#include "../HMIDeviceController.h"

using namespace forte::core::io;

USE_STRING_ID(HMIButton);
USE_STRING_ID(QI);
USE_STRING_ID(LABEL);
USE_STRING_ID(EventInput);
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


DEFINE_FIRMWARE_FB(FORTE_HMIButton, STRID(HMIButton))

const CStringDictionary::TStringId FORTE_HMIButton::scmDataInputNames[] = {STRID(QI), STRID(LABEL), STRID(EventInput)};
const CStringDictionary::TStringId FORTE_HMIButton::scmDataInputTypeIds[] =
    {STRID(BOOL), STRID(WSTRING), STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMIButton::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIButton::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIButton::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_HMIButton::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMIButton::scmEOWith[] = {0, scmWithListDelimiter, 1, 0, scmWithListDelimiter};
const TForteInt16 FORTE_HMIButton::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMIButton::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true}
};
const SFBInterfaceSpec FORTE_HMIButton::scmFBInterfaceSpec = {
    1, scmEventInputNames, nullptr, scmEIWith, scmEIWithIndexes,
    2, scmEventOutputNames, nullptr, scmEOWith, scmEOWithIndexes,
    3, scmDataInputNames, scmDataInputTypeIds,
    2, scmDataOutputNames, scmDataOutputTypeIds,
    0, nullptr,
    2, scmAdapterInstances
};

const TForteUInt8 FORTE_HMIButton::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMIButton::scmSlaveConfigurationIONum = 0;

FORTE_HMIButton::FORTE_HMIButton(const CStringDictionary::TStringId paInstanceNameId,
                                 forte::core::CFBContainer &paContainer) :
  IOConfigFBMultiSlave(scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 96, paContainer, scmFBInterfaceSpec,
                       paInstanceNameId),
  var_QI(0_BOOL),
  var_LABEL(u""_WSTRING),
  var_EventInput(""_STRING),
  var_QO(0_BOOL),
  var_STATUS(u""_WSTRING),
  conn_MAPO(*this, 0),
  conn_IND(*this, 1),
  conn_QI(nullptr),
  conn_LABEL(nullptr),
  conn_EventInput(nullptr),
  conn_QO(*this, 0, var_QO),
  conn_STATUS(*this, 1, var_STATUS) {
}

void FORTE_HMIButton::setInitialValues() {
  var_QI = 0_BOOL;
  var_LABEL = u""_WSTRING;
  var_EventInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIButton::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_LABEL, conn_LABEL);
      readData(2, var_EventInput, conn_EventInput);
      break;
    }
    default: break;
  }
}

void FORTE_HMIButton::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      break;
    }
    case scmEventINDID: {
      writeData(1, var_STATUS, conn_STATUS);
      writeData(0, var_QO, conn_QO);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIButton::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_LABEL;
    case 2: return &var_EventInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIButton::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIButton::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIButton::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_LABEL;
    case 2: return &conn_EventInput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIButton::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMIButton::initHandles() {
  HMIDeviceController::HMIHandleDescriptor desc(var_EventInput.getStorage(), IOMapper::In, 0, CIEC_ANY::e_BOOL);
  initHandle(desc);
}
