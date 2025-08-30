#pragma once

#include "io/configFB/io_master_multi.h"
#include "FORTE_HMIBusAdapter.h"

using namespace forte::core::io;

class FORTE_HMIMaster : IOConfigFBMultiMaster {
    DECLARE_FIRMWARE_FB(FORTE_HMIMaster)

  public:
    FORTE_HMIMaster(CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer);
    ~FORTE_HMIMaster() override = default;

    CIEC_BOOL var_QI;

    CIEC_BOOL var_QO;
    CIEC_WSTRING var_STATUS;

    CEventConnection conn_INITO;

    CDataConnection *conn_QI;

    COutDataConnection<CIEC_BOOL> conn_QO;
    COutDataConnection<CIEC_WSTRING> conn_STATUS;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;

    FORTE_HMIBusAdapter &var_BusAdapterOut() {
      return *static_cast<FORTE_HMIBusAdapter *>(mAdapters[0]);
    };

    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_INIT(const CIEC_BOOL &paQI, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
      var_QI = paQI;
      executeEvent(scmEventINITID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
    }

    void operator()(const CIEC_BOOL &paQI, CIEC_BOOL &paQO, CIEC_WSTRING &paSTATUS) {
      evt_INIT(paQI, paQO, paSTATUS);
    }

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventINITID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
    static const TEventID scmEventINITOID = 0;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];
    static const int scmBusAdapterOutAdpNum = 0;
    static const SAdapterInstanceDef scmAdapterInstances[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

    IODeviceController *createDeviceController(CDeviceExecution &paDeviceExecution) override;
    void setConfig() override;
};
