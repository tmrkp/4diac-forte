#include "FORTE_HMISubject.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMISubject);
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
USE_STRING_ID(HMIBusAdapter);
USE_STRING_ID(BusAdapterIn);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(Event);

DEFINE_FIRMWARE_FB(FORTE_HMISubject, STRID(HMISubject))

const CStringDictionary::TStringId FORTE_HMISubject::scmDataInputNames[] = {STRID(QI), STRID(SubjectName),
                                                                            STRID(IntegerOutput)};
const CStringDictionary::TStringId FORTE_HMISubject::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING),
                                                                              STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMISubject::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMISubject::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMISubject::scmEIWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_HMISubject::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMISubject::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMISubject::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMISubject::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMISubject::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMISubject::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMISubject::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMISubject::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMISubject::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_HMISubject::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMISubject::scmSlaveConfigurationIONum = 0;

FORTE_HMISubject::FORTE_HMISubject(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
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

void FORTE_HMISubject::setInitialValues() {
  var_QI = 0_BOOL;
  var_SubjectName = ""_STRING;
  var_IntegerOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMISubject::readInputData(const TEventID paEIID) {
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

void FORTE_HMISubject::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMISubject::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_SubjectName;
    case 2: return &var_IntegerOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMISubject::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMISubject::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMISubject::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_SubjectName;
    case 2: return &conn_IntegerOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMISubject::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMISubject::initHandles() {
  HMIDeviceController::HMIHandleDescriptor desc(var_IntegerOutput.getStorage(), 0, HMIDeviceController::SUBJECT,
                                                var_SubjectName.getStorage());
  initHandle(desc);
}
