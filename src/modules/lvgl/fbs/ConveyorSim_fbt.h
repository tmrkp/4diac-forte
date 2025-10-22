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

#pragma once

#include "core/basicfb.h"
#include "ATimeOut_adp.h"
#include "core/datatypes/forte_bool.h"
#include "core/datatypes/forte_int.h"
#include "core/datatypes/forte_time.h"
#include "core/iec61131_functions.h"
#include "core/datatypes/forte_array_common.h"
#include "core/datatypes/forte_array.h"
#include "core/datatypes/forte_array_fixed.h"
#include "core/datatypes/forte_array_variable.h"

class FORTE_ConveyorSim final : public CBasicFB {
    DECLARE_FIRMWARE_FB(FORTE_ConveyorSim)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventCmdID = 1;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventStateChangedID = 1;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const int scmTimeOutAdpNum = 0;
    static const SAdapterInstanceDef scmAdapterInstances[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    CIEC_ANY *getVarInternal(size_t) override;

    void alg_leave_left(void);
    void alg_leave_right(void);
    void alg_arrive_left(void);
    void alg_arrive_right(void);

    static const TForteInt16 scmStateSTART = 0;
    static const TForteInt16 scmStatePacket_links = 1;
    static const TForteInt16 scmStatePacket_unterwegs_rechts = 2;
    static const TForteInt16 scmStatePacket_rechts = 3;
    static const TForteInt16 scmStatePacket_unterwegs_links = 4;

    void enterStateSTART(CEventChainExecutionThread *const paECET);
    void enterStatePacket_links(CEventChainExecutionThread *const paECET);
    void enterStatePacket_unterwegs_rechts(CEventChainExecutionThread *const paECET);
    void enterStatePacket_rechts(CEventChainExecutionThread *const paECET);
    void enterStatePacket_unterwegs_links(CEventChainExecutionThread *const paECET);

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_ConveyorSim(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);
    bool initialize() override;

    CIEC_INT var_Speed;

    CIEC_BOOL var_L1;
    CIEC_BOOL var_L2;

    FORTE_ATimeOut var_TimeOut;

    CIEC_BOOL var_conn_L1;
    CIEC_BOOL var_conn_L2;

    CEventConnection conn_INITO;
    CEventConnection conn_StateChanged;

    CDataConnection *conn_Speed;

    COutDataConnection<CIEC_BOOL> conn_L1;
    COutDataConnection<CIEC_BOOL> conn_L2;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CAdapter *getAdapterUnchecked(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_INT &paSpeed, CIEC_BOOL &paL1, CIEC_BOOL &paL2) {
      var_Speed = paSpeed;
      executeEvent(scmEventINITID, nullptr);
      paL1 = var_L1;
      paL2 = var_L2;
    }

    void evt_Cmd(const CIEC_INT &paSpeed, CIEC_BOOL &paL1, CIEC_BOOL &paL2) {
      var_Speed = paSpeed;
      executeEvent(scmEventCmdID, nullptr);
      paL1 = var_L1;
      paL2 = var_L2;
    }
};
