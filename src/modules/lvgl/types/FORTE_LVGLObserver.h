#pragma once

#include "io/configFB/io_slave_multi.h"
#include "io/device/io_controller.h"
#include "FORTE_LVGLBusAdapter.h"

using namespace forte::core::io;

class FORTE_LVGLObserver final : public IOConfigFBMultiSlave {
    DECLARE_FIRMWARE_FB(FORTE_LVGLObserver)

  public:
    FORTE_LVGLObserver(CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer);
    ~FORTE_LVGLObserver() override = default;

    CIEC_BOOL var_QI;
    CIEC_STRING var_SubjectName;
    CIEC_STRING var_IntegerInput;

    CIEC_BOOL var_QO;
    CIEC_WSTRING var_STATUS;

    CIEC_BOOL var_conn_QO;
    CIEC_WSTRING var_conn_STATUS;

    CEventConnection conn_MAPO;
    CEventConnection conn_IND;

    CDataConnection *conn_QI;
    CDataConnection *conn_SubjectName;
    CDataConnection *conn_IntegerInput;

    COutDataConnection<CIEC_BOOL> conn_QO;
    COutDataConnection<CIEC_WSTRING> conn_STATUS;

    CIEC_ANY *getDI(size_t) override;
    CIEC_ANY *getDO(size_t) override;

    CEventConnection *getEOConUnchecked(TPortId) override;
    CDataConnection **getDIConUnchecked(TPortId) override;
    CDataConnection *getDOConUnchecked(TPortId) override;

    void evt_MAP(const CIEC_BOOL &paQI,
                 const CIEC_STRING &paSubjectName,
                 const CIEC_STRING &paIntegerInput,
                 CIEC_BOOL &paQO,
                 CIEC_WSTRING &paSTATUS) {
      var_QI = paQI;
      var_SubjectName = paSubjectName;
      var_IntegerInput = paIntegerInput;
      executeEvent(scmEventMAPID, nullptr);
      paQO = var_QO;
      paSTATUS = var_STATUS;
    }

    void operator()(const CIEC_BOOL &paQI,
                    const CIEC_STRING &paSubjectName,
                    const CIEC_STRING &paIntegerInput,
                    CIEC_BOOL &paQO,
                    CIEC_WSTRING &paSTATUS) {
      evt_MAP(paQI, paSubjectName, paIntegerInput, paQO, paSTATUS);
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
    static const CStringDictionary::TStringId scmEventInputNames[];
    static const CStringDictionary::TStringId scmEventInputTypeIds[];
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
