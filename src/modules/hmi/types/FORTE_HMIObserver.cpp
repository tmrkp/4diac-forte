#include "FORTE_HMIObserver.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMIObserver);
USE_STRING_ID(QI);
USE_STRING_ID(SubjectName);
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

DEFINE_FIRMWARE_FB(FORTE_HMIObserver, STRID(HMIObserver))

const CStringDictionary::TStringId FORTE_HMIObserver::scmDataInputNames[] = {STRID(QI), STRID(SubjectName),
                                                                             STRID(IntegerInput)};
const CStringDictionary::TStringId FORTE_HMIObserver::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING),
                                                                               STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMIObserver::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIObserver::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIObserver::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_HMIObserver::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIObserver::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMIObserver::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMIObserver::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMIObserver::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMIObserver::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMIObserver::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMIObserver::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMIObserver::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_HMIObserver::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMIObserver::scmSlaveConfigurationIONum = 0;

FORTE_HMIObserver::FORTE_HMIObserver(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_SubjectName(""_STRING),
    var_IntegerInput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_SubjectName(nullptr),
    conn_IntegerInput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMIObserver::setInitialValues() {
  var_QI = 0_BOOL;
  var_SubjectName = ""_STRING;
  var_IntegerInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIObserver::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_SubjectName, conn_SubjectName);
      readData(2, var_IntegerInput, conn_IntegerInput);
      break;
    }
    default: break;
  }
}

void FORTE_HMIObserver::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIObserver::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_SubjectName;
    case 2: return &var_IntegerInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIObserver::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIObserver::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIObserver::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_SubjectName;
    case 2: return &conn_IntegerInput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIObserver::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMIObserver::initHandles() {
  lv_subject_t *subject =
      static_cast<HMIDeviceController &>(getController()).getConnector().connectObserver(var_SubjectName.getStorage());

  if (!subject) {
    // TODO: set status
    return;
  }

  HMIDeviceController::HMISubjectHandleDescriptor desc(var_IntegerInput.getStorage(), IOMapper::In, 0, subject);
  initHandle(desc);
}
