#include "HMIMaster.h"

USE_STRING_ID(BOOL);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(EInit);
USE_STRING_ID(Event);
USE_STRING_ID(IND);
USE_STRING_ID(INIT);
USE_STRING_ID(INITO);
USE_STRING_ID(QI);
USE_STRING_ID(QO);
USE_STRING_ID(STATUS);
USE_STRING_ID(UINT);
USE_STRING_ID(HMIBusAdapter);
USE_STRING_ID(HMIMaster);
USE_STRING_ID(WSTRING);

#include "../HMIDeviceController.h"

DEFINE_FIRMWARE_FB(FORTE_HMIMaster, STRID(HMIMaster))

const CStringDictionary::TStringId FORTE_HMIMaster::scmDataInputNames[] = {STRID(QI)};
const CStringDictionary::TStringId FORTE_HMIMaster::scmDataInputTypeIds[] = {STRID(BOOL)};
const CStringDictionary::TStringId FORTE_HMIMaster::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIMaster::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIMaster::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_HMIMaster::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIMaster::scmEventInputNames[] = {STRID(INIT)};
const CStringDictionary::TStringId FORTE_HMIMaster::scmEventInputTypeIds[] = {STRID(EInit)};
const TDataIOID FORTE_HMIMaster::scmEOWith[] = {0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMIMaster::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIMaster::scmEventOutputNames[] = {STRID(INITO)};
const CStringDictionary::TStringId FORTE_HMIMaster::scmEventOutputTypeIds[] = {STRID(EInit)};
const SAdapterInstanceDef FORTE_HMIMaster::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true}};
const SFBInterfaceSpec FORTE_HMIMaster::scmFBInterfaceSpec = {
    1, scmEventInputNames, nullptr, scmEIWith, scmEIWithIndexes,
    1, scmEventOutputNames, nullptr, scmEOWith, scmEOWithIndexes,
    1, scmDataInputNames, scmDataInputTypeIds,
    2, scmDataOutputNames, scmDataOutputTypeIds,
    0, nullptr,
    1, scmAdapterInstances
};

FORTE_HMIMaster::FORTE_HMIMaster(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
  IOConfigFBMultiMaster(paContainer, scmFBInterfaceSpec, paInstanceNameId),
  var_QI(0_BOOL),
  var_QO(0_BOOL),
  var_STATUS(u""_WSTRING),
  conn_INITO(*this, 0),
  conn_QI(nullptr),
  conn_QO(*this, 0, var_QO),
  conn_STATUS(*this, 1, var_STATUS) {
}

void FORTE_HMIMaster::setInitialValues() {
  var_QI = 0_BOOL;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIMaster::setConfig() {
  HMIDeviceController::HMIConfig config;
  getDeviceController()->setConfig(&config);
}

IODeviceController *FORTE_HMIMaster::createDeviceController(CDeviceExecution &paDeviceExecution) {
  return new HMIDeviceController(paDeviceExecution);
}

void FORTE_HMIMaster::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      break;
    }
    default: break;
  }
}

void FORTE_HMIMaster::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIMaster::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIMaster::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIMaster::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_INITO;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIMaster::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIMaster::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}
