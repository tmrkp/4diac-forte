#include "FORTE_LVGLObserver.h"

#include "LVGLDeviceController.h"

USE_STRING_ID(LVGLObserver);
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
USE_STRING_ID(LVGLBusAdapter);
USE_STRING_ID(BusAdapterIn);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(Event);

DEFINE_FIRMWARE_FB(FORTE_LVGLObserver, STRID(LVGLObserver))

const CStringDictionary::TStringId FORTE_LVGLObserver::scmDataInputNames[] = {STRID(QI), STRID(SubjectName),
                                                                             STRID(IntegerInput)};
const CStringDictionary::TStringId FORTE_LVGLObserver::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING),
                                                                               STRID(STRING)};
const CStringDictionary::TStringId FORTE_LVGLObserver::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_LVGLObserver::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_LVGLObserver::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLObserver::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLObserver::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_LVGLObserver::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLObserver::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLObserver::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_LVGLObserver::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_LVGLObserver::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_LVGLObserver::scmAdapterInstances[] = {
    {STRID(LVGLBusAdapter), STRID(BusAdapterOut), true},
    {STRID(LVGLBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_LVGLObserver::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_LVGLObserver::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_LVGLObserver::scmSlaveConfigurationIONum = 0;

FORTE_LVGLObserver::FORTE_LVGLObserver(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
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

void FORTE_LVGLObserver::setInitialValues() {
  var_QI = 0_BOOL;
  var_SubjectName = ""_STRING;
  var_IntegerInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_LVGLObserver::readInputData(const TEventID paEIID) {
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

void FORTE_LVGLObserver::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_LVGLObserver::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_SubjectName;
    case 2: return &var_IntegerInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LVGLObserver::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_LVGLObserver::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_LVGLObserver::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_SubjectName;
    case 2: return &conn_IntegerInput;
  }
  return nullptr;
}

CDataConnection *FORTE_LVGLObserver::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_LVGLObserver::initHandles() {
  lv_subject_t *subject =
      static_cast<LVGLDeviceController &>(getController()).getConnector().connectObserver(var_SubjectName.getStorage());

  if (!subject) {
    return;
  }

  LVGLDeviceController::LVGLSubjectHandleDescriptor desc(var_IntegerInput.getStorage(), IOMapper::In, 0, subject);
  initHandle(desc);
}
