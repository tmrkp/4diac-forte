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

#pragma once

#include "funcbloc.h"
#include "forte_any_variant.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"
#include "io/configFB/io_master_multi.h"
#include "io/device/io_controller.h"

class FORTE_HMI final : public CFunctionBlock {
    DECLARE_FIRMWARE_FB(FORTE_HMI)

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TEventID scmEventREQID = 1;
    static const TEventID scmEventRSPID = 2;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const TEventID scmEventINITOID = 0;
    static const TEventID scmEventCNFID = 1;
    static const TEventID scmEventINDID = 2;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) override;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

  public:
    FORTE_HMI(CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer);

    CIEC_BOOL var_QI;
    CIEC_WSTRING var_PARAMS;
    CIEC_ANY_VARIANT var_SD;

    CIEC_BOOL var_QO;
    CIEC_WSTRING var_STATUS;
    CIEC_ANY_VARIANT var_RD;

    CIEC_BOOL var_conn_QO;
    CIEC_WSTRING var_conn_STATUS;
    CIEC_ANY_VARIANT var_conn_RD;

    CEventConnection conn_INITO;
    CEventConnection conn_CNF;
    CEventConnection conn_IND;

    CDataConnection *conn_QI;
    CDataConnection *conn_PARAMS;
    CDataConnection *conn_SD;

    COutDataConnection<CIEC_BOOL> conn_QO;
    COutDataConnection<CIEC_WSTRING> conn_STATUS;
    COutDataConnection<CIEC_ANY_VARIANT> conn_RD;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;
    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI,
                  const CIEC_WSTRING &paPARAMS,
                  const CIEC_ANY &paSD,
                  CIEC_BOOL &paQO,
                  CIEC_WSTRING &paSTATUS,
                  CIEC_ANY &paRD) {
      var_QI = paQI;
      var_PARAMS = paPARAMS;
      var_SD = paSD;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paRD.setValue(var_RD.unwrap());
    }

    void evt_REQ(const CIEC_BOOL &paQI,
                 const CIEC_WSTRING &paPARAMS,
                 const CIEC_ANY &paSD,
                 CIEC_BOOL &paQO,
                 CIEC_WSTRING &paSTATUS,
                 CIEC_ANY &paRD) {
      var_QI = paQI;
      var_PARAMS = paPARAMS;
      var_SD = paSD;
      executeEvent(scmEventREQID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paRD.setValue(var_RD.unwrap());
    }

    void evt_RSP(const CIEC_BOOL &paQI,
                 const CIEC_WSTRING &paPARAMS,
                 const CIEC_ANY &paSD,
                 CIEC_BOOL &paQO,
                 CIEC_WSTRING &paSTATUS,
                 CIEC_ANY &paRD) {
      var_QI = paQI;
      var_PARAMS = paPARAMS;
      var_SD = paSD;
      executeEvent(scmEventRSPID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
      paRD.setValue(var_RD.unwrap());
    }

    void operator()(const CIEC_BOOL &paQI,
                    const CIEC_WSTRING &paPARAMS,
                    const CIEC_ANY &paSD,
                    CIEC_BOOL &paQO,
                    CIEC_WSTRING &paSTATUS,
                    CIEC_ANY &paRD) {
      evt_INIT(paQI, paPARAMS, paSD, paQO, paSTATUS, paRD);
    }
};

