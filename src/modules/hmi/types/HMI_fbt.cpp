/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: HMI
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2025-06-08/tim -  -
 *************************************************************************/

#include "HMI_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "HMI_fbt_gen.cpp"
#endif

#include "device.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "HMIDeviceController.h"

USE_STRING_ID(HMI)
USE_STRING_ID(QI)
USE_STRING_ID(PARAMS)
USE_STRING_ID(SD)
USE_STRING_ID(BOOL)
USE_STRING_ID(WSTRING)
USE_STRING_ID(ANY)
USE_STRING_ID(QO)
USE_STRING_ID(STATUS)
USE_STRING_ID(RD)
USE_STRING_ID(INIT)
USE_STRING_ID(REQ)
USE_STRING_ID(RSP)
USE_STRING_ID(INITO)
USE_STRING_ID(CNF)
USE_STRING_ID(IND)

DEFINE_FIRMWARE_FB(FORTE_HMI, STRID(HMI))

const CStringDictionary::TStringId FORTE_HMI::scmDataInputNames[] = {STRID(QI), STRID(PARAMS), STRID(SD)};
const CStringDictionary::TStringId FORTE_HMI::scmDataInputTypeIds[] = {STRID(BOOL), STRID(WSTRING), STRID(ANY)};
const CStringDictionary::TStringId FORTE_HMI::scmDataOutputNames[] = {STRID(QO), STRID(STATUS), STRID(RD)};
const CStringDictionary::TStringId FORTE_HMI::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING), STRID(ANY)};
const TDataIOID FORTE_HMI::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 2, scmWithListDelimiter, 0, 2,
                                          scmWithListDelimiter};
const TForteInt16 FORTE_HMI::scmEIWithIndexes[] = {0, 3, 6};
const CStringDictionary::TStringId FORTE_HMI::scmEventInputNames[] = {STRID(INIT), STRID(REQ), STRID(RSP)};
const TDataIOID FORTE_HMI::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter, 0, 1, 2,
                                          scmWithListDelimiter};
const TForteInt16 FORTE_HMI::scmEOWithIndexes[] = {0, 3, 7};
const CStringDictionary::TStringId FORTE_HMI::scmEventOutputNames[] = {STRID(INITO), STRID(CNF), STRID(IND)};
const SFBInterfaceSpec FORTE_HMI::scmFBInterfaceSpec = {
    3, scmEventInputNames, nullptr, scmEIWith, scmEIWithIndexes,
    3, scmEventOutputNames, nullptr, scmEOWith, scmEOWithIndexes,
    3, scmDataInputNames, scmDataInputTypeIds,
    3, scmDataOutputNames, scmDataOutputTypeIds,
    0, nullptr,
    0, nullptr
};

FORTE_HMI::FORTE_HMI(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
  CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
  var_QI(0_BOOL),
  var_PARAMS(u""_WSTRING),
  var_SD(CIEC_ANY_VARIANT()),
  var_QO(0_BOOL),
  var_STATUS(u""_WSTRING),
  var_RD(CIEC_ANY_VARIANT()),
  var_conn_QO(var_QO),
  var_conn_STATUS(var_STATUS),
  var_conn_RD(var_RD),
  conn_INITO(*this, 0),
  conn_CNF(*this, 1),
  conn_IND(*this, 2),
  conn_QI(nullptr),
  conn_PARAMS(nullptr),
  conn_SD(nullptr),
  conn_QO(*this, 0, var_conn_QO),
  conn_STATUS(*this, 1, var_conn_STATUS),
  conn_RD(*this, 2, var_conn_RD) {
};

void FORTE_HMI::setInitialValues() {
  var_QI = 0_BOOL;
  var_PARAMS = u""_WSTRING;
  var_SD = CIEC_ANY_VARIANT();
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
  var_RD = CIEC_ANY_VARIANT();
}

void FORTE_HMI::executeEvent(const TEventID paEIID, CEventChainExecutionThread *const paECET) {
  switch (paEIID) {
    case scmEventINITID:
      // code for init event
      sendOutputEvent(scmEventCNFID, paECET);
      break;
    case scmEventREQID:
      // code for req event

      sendOutputEvent(scmEventCNFID, paECET);
      break;
    case scmEventRSPID:
      // code for rsp event

      sendOutputEvent(scmEventCNFID, paECET);
      break;
  }
}

void FORTE_HMI::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_PARAMS, conn_PARAMS);
      break;
    }
    case scmEventREQID: {
      readData(0, var_QI, conn_QI);
      readData(2, var_SD, conn_SD);
      break;
    }
    case scmEventRSPID: {
      readData(0, var_QI, conn_QI);
      readData(2, var_SD, conn_SD);
      break;
    }
    default: break;
  }
}

void FORTE_HMI::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    case scmEventCNFID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_RD, conn_RD);
      break;
    }
    case scmEventINDID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      writeData(2, var_RD, conn_RD);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMI::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_PARAMS;
    case 2: return &var_SD;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMI::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
    case 2: return &var_RD;
  }
  return nullptr;
}

CEventConnection *FORTE_HMI::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_CNF;
    case 2: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMI::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_PARAMS;
    case 2: return &conn_SD;
  }
  return nullptr;
}

CDataConnection *FORTE_HMI::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
    case 2: return &conn_RD;
  }
  return nullptr;
}
