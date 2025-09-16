#include "FORTE_LVGLSubject.h"

#include "LVGLDeviceController.h"

USE_STRING_ID(LVGLSubject);
USE_STRING_ID(QI);
USE_STRING_ID(SubjectName);
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
USE_STRING_ID(LVGLBusAdapter);
USE_STRING_ID(BusAdapterIn);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(Event);

DEFINE_FIRMWARE_FB(FORTE_LVGLSubject, STRID(LVGLSubject))

const CStringDictionary::TStringId FORTE_LVGLSubject::scmDataInputNames[] = {STRID(QI), STRID(SubjectName),
                                                                            STRID(IntegerOutput)};
const CStringDictionary::TStringId FORTE_LVGLSubject::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING),
                                                                              STRID(STRING)};
const CStringDictionary::TStringId FORTE_LVGLSubject::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_LVGLSubject::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_LVGLSubject::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLSubject::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLSubject::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_LVGLSubject::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLSubject::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLSubject::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_LVGLSubject::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_LVGLSubject::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_LVGLSubject::scmAdapterInstances[] = {
    {STRID(LVGLBusAdapter), STRID(BusAdapterOut), true},
    {STRID(LVGLBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_LVGLSubject::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_LVGLSubject::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_LVGLSubject::scmSlaveConfigurationIONum = 0;

FORTE_LVGLSubject::FORTE_LVGLSubject(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_SubjectName(""_STRING),
    var_IntegerOutput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_SubjectName(nullptr),
    conn_IntegerOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_LVGLSubject::setInitialValues() {
  var_QI = 0_BOOL;
  var_SubjectName = ""_STRING;
  var_IntegerOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_LVGLSubject::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_SubjectName, conn_SubjectName);
      readData(2, var_IntegerOutput, conn_IntegerOutput);
      break;
    }
    default: break;
  }
}

void FORTE_LVGLSubject::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_LVGLSubject::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_SubjectName;
    case 2: return &var_IntegerOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LVGLSubject::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_LVGLSubject::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_LVGLSubject::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_SubjectName;
    case 2: return &conn_IntegerOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_LVGLSubject::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_LVGLSubject::initHandles() {
  lv_subject_t *subject =
      static_cast<LVGLDeviceController &>(getController()).getConnector().connectSubject(var_SubjectName.getStorage());

  if (!subject) {
    return;
  }

  LVGLDeviceController::LVGLSubjectHandleDescriptor desc(var_IntegerOutput.getStorage(), IOMapper::Out, 0, subject);
  initHandle(desc);
}
