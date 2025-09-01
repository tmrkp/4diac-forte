#pragma once

#include "io/configFB/io_slave_multi.h"
#include "io/device/io_controller.h"
#include "../FORTE_HMIBusAdapter.h"

using namespace forte::core::io;

class FORTE_HMINumber final : public IOConfigFBMultiSlave {
    DECLARE_FIRMWARE_FB(FORTE_HMINumber)

  public:
    FORTE_HMINumber(CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer);
    ~FORTE_HMINumber() override = default;

    CIEC_BOOL var_QI;
    CIEC_STRING var_Label;
    CIEC_STRING var_WidgetName;
    CIEC_STRING var_IntegerOutput;

    CIEC_BOOL var_QO;
    CIEC_WSTRING var_STATUS;

    CIEC_BOOL var_conn_QO;
    CIEC_WSTRING var_conn_STATUS;

    CEventConnection conn_MAPO;
    CEventConnection conn_IND;

    CDataConnection *conn_QI;
    CDataConnection *conn_Label;
    CDataConnection *conn_WidgetName;
    CDataConnection *conn_IntegerOutput;

    COutDataConnection<CIEC_BOOL> conn_QO;
    COutDataConnection<CIEC_WSTRING> conn_STATUS;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;

    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_MAP(const CIEC_BOOL &paQI,
                 const CIEC_STRING &paLabel,
                 const CIEC_STRING &paWidgetName,
                 const CIEC_STRING &paIntegerOutput,
                 CIEC_BOOL &paQO,
                 CIEC_WSTRING &paSTATUS) {
      var_QI = paQI;
      var_Label = paLabel;
      var_WidgetName = paWidgetName;
      var_IntegerOutput = paIntegerOutput;
      executeEvent(scmEventMAPID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
    }

    void operator()(const CIEC_BOOL &paQI,
                    const CIEC_STRING &paLabel,
                    const CIEC_STRING &paWidgetName,
                    const CIEC_STRING &paIntegerOutput,
                    CIEC_BOOL &paQO,
                    CIEC_WSTRING &paSTATUS) {
      evt_MAP(paQI, paLabel, paWidgetName, paIntegerOutput, paQO, paSTATUS);
    }

  protected:
    void initHandles() override;

  private:
    static const CStringDictionary::TStringId scmDataInputNames[];
    static const CStringDictionary::TStringId scmDataInputTypeIds[];
    static const CStringDictionary::TStringId scmDataOutputNames[];
    static const CStringDictionary::TStringId scmDataOutputTypeIds[];
    static const TEventID scmEventMAPID = 0;
    static const TDataIOID scmEIWith[];
    static const TForteInt16 scmEIWithIndexes[];
    static const CStringDictionary::TStringId scmIntegerOutputNames[];
    static const CStringDictionary::TStringId scmIntegerOutputTypeIds[];
    static const TEventID scmEventMAPOID = 0;
    static const TEventID scmEventINDID = 1;
    static const TDataIOID scmEOWith[];
    static const TForteInt16 scmEOWithIndexes[];
    static const CStringDictionary::TStringId scmEventOutputNames[];
    static const CStringDictionary::TStringId scmEventOutputTypeIds[];
    static const int scmBusAdapterInAdpNum = 0;
    static const int scmBusAdapterOutAdpNum = 1;
    static const SAdapterInstanceDef scmAdapterInstances[];

    static const SFBInterfaceSpec scmFBInterfaceSpec;

    void readInputData(TEventID paEIID) override;
    void writeOutputData(TEventID paEIID) override;
    void setInitialValues() override;

    static const TForteUInt8 scmSlaveConfigurationIO[];
    static const TForteUInt8 scmSlaveConfigurationIONum;
};
