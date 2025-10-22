/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ConveyorSim
 *** Description: Basic FB with empty ECC
 *** Version:
 ***     1.0: 2025-09-10/tim -  -
 *************************************************************************/

#include "ConveyorSim_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ConveyorSim_fbt_gen.cpp"
#endif

#include "ATimeOut_adp.h"
#include "core/datatypes/forte_bool.h"
#include "core/datatypes/forte_int.h"
#include "core/datatypes/forte_time.h"
#include "core/iec61131_functions.h"
#include "core/datatypes/forte_array_common.h"
#include "core/datatypes/forte_array.h"
#include "core/datatypes/forte_array_fixed.h"
#include "core/datatypes/forte_array_variable.h"

USE_STRING_ID(ConveyorSim)
USE_STRING_ID(Speed)
USE_STRING_ID(INT)
USE_STRING_ID(L1)
USE_STRING_ID(L2)
USE_STRING_ID(BOOL)
USE_STRING_ID(INIT)
USE_STRING_ID(Cmd)
USE_STRING_ID(INITO)
USE_STRING_ID(StateChanged)
USE_STRING_ID(ATimeOut)
USE_STRING_ID(TimeOut)

DEFINE_FIRMWARE_FB(FORTE_ConveyorSim, STRID(ConveyorSim))

const CStringDictionary::TStringId FORTE_ConveyorSim::scmDataInputNames[] = {STRID(Speed)};
const CStringDictionary::TStringId FORTE_ConveyorSim::scmDataInputTypeIds[] = {STRID(INT)};
const CStringDictionary::TStringId FORTE_ConveyorSim::scmDataOutputNames[] = {STRID(L1), STRID(L2)};
const CStringDictionary::TStringId FORTE_ConveyorSim::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(BOOL)};
const TDataIOID FORTE_ConveyorSim::scmEIWith[] = {0, scmWithListDelimiter, 0, scmWithListDelimiter};
const TForteInt16 FORTE_ConveyorSim::scmEIWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_ConveyorSim::scmEventInputNames[] = {STRID(INIT), STRID(Cmd)};
const TDataIOID FORTE_ConveyorSim::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_ConveyorSim::scmEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_ConveyorSim::scmEventOutputNames[] = {STRID(INITO), STRID(StateChanged)};
const SAdapterInstanceDef FORTE_ConveyorSim::scmAdapterInstances[] = {{STRID(ATimeOut), STRID(TimeOut), true}};
const SFBInterfaceSpec FORTE_ConveyorSim::scmFBInterfaceSpec = {2,
                                                                scmEventInputNames,
                                                                nullptr,
                                                                scmEIWith,
                                                                scmEIWithIndexes,
                                                                2,
                                                                scmEventOutputNames,
                                                                nullptr,
                                                                scmEOWith,
                                                                scmEOWithIndexes,
                                                                1,
                                                                scmDataInputNames,
                                                                scmDataInputTypeIds,
                                                                2,
                                                                scmDataOutputNames,
                                                                scmDataOutputTypeIds,
                                                                0,
                                                                nullptr,
                                                                1,
                                                                scmAdapterInstances};

FORTE_ConveyorSim::FORTE_ConveyorSim(const CStringDictionary::TStringId paInstanceNameId,
                                     forte::core::CFBContainer &paContainer) :
    CBasicFB(paContainer, scmFBInterfaceSpec, paInstanceNameId, nullptr),
    var_Speed(0_INT),
    var_L1(0_BOOL),
    var_L2(0_BOOL),
    var_TimeOut(STRID(TimeOut), *this, true),
    var_conn_L1(var_L1),
    var_conn_L2(var_L2),
    conn_INITO(*this, 0),
    conn_StateChanged(*this, 1),
    conn_Speed(nullptr),
    conn_L1(*this, 0, var_conn_L1),
    conn_L2(*this, 1, var_conn_L2) {
}

bool FORTE_ConveyorSim::initialize() {
  if (!var_TimeOut.initialize()) {
    return false;
  }
  var_TimeOut.setParentFB(this, 0);
  return CBasicFB::initialize();
}

void FORTE_ConveyorSim::setInitialValues() {
  var_Speed = 0_INT;
  var_L1 = 0_BOOL;
  var_L2 = 0_BOOL;
}

void FORTE_ConveyorSim::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  do {
    switch (mECCState) {
      case scmStateSTART:
        if (scmEventINITID == paEIID)
          enterStatePacket_links(paECET);
        else
          return; // no transition cleared
        break;
      case scmStatePacket_links:
        if ((scmEventCmdID == paEIID) && (func_GT(var_Speed, 0_INT)))
          enterStatePacket_unterwegs_rechts(paECET);
        else
          return; // no transition cleared
        break;
      case scmStatePacket_unterwegs_rechts:
        if (var_TimeOut.evt_TimeOut() == paEIID)
          enterStatePacket_rechts(paECET);
        else
          return; // no transition cleared
        break;
      case scmStatePacket_rechts:
        if ((scmEventCmdID == paEIID) && (func_LT(var_Speed, 0_INT)))
          enterStatePacket_unterwegs_links(paECET);
        else
          return; // no transition cleared
        break;
      case scmStatePacket_unterwegs_links:
        if (var_TimeOut.evt_TimeOut() == paEIID)
          enterStatePacket_links(paECET);
        else
          return; // no transition cleared
        break;
      default:
        DEVLOG_ERROR("The state is not in the valid range! The state value is: %d. The max value can be: 5.",
                     mECCState.operator TForteUInt16());
        mECCState = 0; // 0 is always the initial state
        return;
    }
    paEIID = cgInvalidEventID; // we have to clear the event after the first check in order to ensure correct behavior
  } while (true);
}

void FORTE_ConveyorSim::enterStateSTART(CEventChainExecutionThread *const) {
  mECCState = scmStateSTART;
}

void FORTE_ConveyorSim::enterStatePacket_links(CEventChainExecutionThread *const paECET) {
  mECCState = scmStatePacket_links;
  alg_arrive_left();
  sendOutputEvent(scmEventStateChangedID, paECET);
}

void FORTE_ConveyorSim::enterStatePacket_unterwegs_rechts(CEventChainExecutionThread *const paECET) {
  mECCState = scmStatePacket_unterwegs_rechts;
  alg_leave_left();
  sendOutputEvent(scmEventStateChangedID, paECET);
  sendAdapterEvent(scmTimeOutAdpNum, FORTE_ATimeOut::scmEventSTARTID, paECET);
}

void FORTE_ConveyorSim::enterStatePacket_rechts(CEventChainExecutionThread *const paECET) {
  mECCState = scmStatePacket_rechts;
  alg_arrive_right();
  sendOutputEvent(scmEventStateChangedID, paECET);
}

void FORTE_ConveyorSim::enterStatePacket_unterwegs_links(CEventChainExecutionThread *const paECET) {
  mECCState = scmStatePacket_unterwegs_links;
  alg_leave_right();
  sendOutputEvent(scmEventStateChangedID, paECET);
  sendAdapterEvent(scmTimeOutAdpNum, FORTE_ATimeOut::scmEventSTARTID, paECET);
}

void FORTE_ConveyorSim::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITID: {
      readData(0, var_Speed, conn_Speed);
      break;
    }
    case scmEventCmdID: {
      readData(0, var_Speed, conn_Speed);
      break;
    }
    default: break;
  }
}

void FORTE_ConveyorSim::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventINITOID: {
      writeData(0, var_L1, conn_L1);
      writeData(1, var_L2, conn_L2);
      break;
    }
    case scmEventStateChangedID: {
      writeData(0, var_L1, conn_L1);
      writeData(1, var_L2, conn_L2);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_ConveyorSim::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_Speed;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ConveyorSim::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_L1;
    case 1: return &var_L2;
  }
  return nullptr;
}

CAdapter *FORTE_ConveyorSim::getAdapterUnchecked(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_TimeOut;
  }
  return nullptr;
}

CEventConnection *FORTE_ConveyorSim::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_INITO;
    case 1: return &conn_StateChanged;
  }
  return nullptr;
}

CDataConnection **FORTE_ConveyorSim::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_Speed;
  }
  return nullptr;
}

CDataConnection *FORTE_ConveyorSim::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_L1;
    case 1: return &conn_L2;
  }
  return nullptr;
}

CIEC_ANY *FORTE_ConveyorSim::getVarInternal(size_t) {
  return nullptr;
}

void FORTE_ConveyorSim::alg_leave_left(void) {

#line 2 "ConveyorSim.fbt"
  var_L1 = false_BOOL;
#line 3 "ConveyorSim.fbt"
  var_TimeOut.var_DT() = 3000000000_TIME;
}

void FORTE_ConveyorSim::alg_leave_right(void) {

#line 7 "ConveyorSim.fbt"
  var_L2 = false_BOOL;
#line 8 "ConveyorSim.fbt"
  var_TimeOut.var_DT() = 3000000000_TIME;
}

void FORTE_ConveyorSim::alg_arrive_left(void) {

#line 12 "ConveyorSim.fbt"
  var_L1 = true_BOOL;
}

void FORTE_ConveyorSim::alg_arrive_right(void) {

#line 16 "ConveyorSim.fbt"
  var_L2 = true_BOOL;
}
