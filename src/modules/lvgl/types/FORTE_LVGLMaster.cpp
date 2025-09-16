#include "FORTE_LVGLMaster.h"

USE_STRING_ID(BOOL);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(Event);
USE_STRING_ID(IND);
USE_STRING_ID(INIT);
USE_STRING_ID(INITO);
USE_STRING_ID(QI);
USE_STRING_ID(QO);
USE_STRING_ID(STATUS);
USE_STRING_ID(UINT);
USE_STRING_ID(LVGLBusAdapter);
USE_STRING_ID(LVGLMaster);
USE_STRING_ID(WSTRING);

#include "../LVGLDeviceController.h"

DEFINE_FIRMWARE_FB(FORTE_LVGLMaster, STRID(LVGLMaster))

const CStringDictionary::TStringId FORTE_LVGLMaster::scmDataInputNames[] = {STRID(QI)};
const CStringDictionary::TStringId FORTE_LVGLMaster::scmDataInputTypeIds[] = {STRID(BOOL)};
const CStringDictionary::TStringId FORTE_LVGLMaster::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_LVGLMaster::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_LVGLMaster::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLMaster::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLMaster::scmEventInputNames[] = {STRID(INIT)};
const CStringDictionary::TStringId FORTE_LVGLMaster::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLMaster::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLMaster::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLMaster::scmEventOutputNames[] = {STRID(INITO)};
const CStringDictionary::TStringId FORTE_LVGLMaster::scmEventOutputTypeIds[] = {STRID(Event)};
const SAdapterInstanceDef FORTE_LVGLMaster::scmAdapterInstances[] = {
    {STRID(LVGLBusAdapter), STRID(BusAdapterOut), true}};
const SFBInterfaceSpec FORTE_LVGLMaster::scmFBInterfaceSpec = {
    1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
    1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
    1, scmDataInputNames, scmDataInputTypeIds,
    2, scmDataOutputNames, scmDataOutputTypeIds,
    0, nullptr,
    1, scmAdapterInstances
};

FORTE_LVGLMaster::FORTE_LVGLMaster(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
  IOConfigFBMultiMaster(paContainer, scmFBInterfaceSpec, paInstanceNameId),
  var_QI(0_BOOL),
  var_QO(0_BOOL),
  var_STATUS(u""_WSTRING),
  conn_INITO(*this, 0),
  conn_QI(nullptr),
  conn_QO(*this, 0, var_QO),
  conn_STATUS(*this, 1, var_STATUS) {
}

void FORTE_LVGLMaster::setInitialValues() {
  var_QI = 0_BOOL;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_LVGLMaster::setConfig() {
  LVGLDeviceController::LVGLConfig config;
  getDeviceController()->setConfig(&config);
}

IODeviceController *FORTE_LVGLMaster::createDeviceController(CDeviceExecution &paDeviceExecution) {
  return new LVGLDeviceController(paDeviceExecution);
}

void FORTE_LVGLMaster::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default: break;
  }
}

void FORTE_LVGLMaster::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_LVGLMaster::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LVGLMaster::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_LVGLMaster::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_INITO;
  }
  return nullptr;
}

CDataConnection **FORTE_LVGLMaster::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
  }
  return nullptr;
}

CDataConnection *FORTE_LVGLMaster::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}
