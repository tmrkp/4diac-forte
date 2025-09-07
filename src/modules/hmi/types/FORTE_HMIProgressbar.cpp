#include "FORTE_HMIProgressbar.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMIProgressbar);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(MinRange);
USE_STRING_ID(MaxRange);
USE_STRING_ID(WidgetName);
USE_STRING_ID(IntegerOutput);
USE_STRING_ID(BOOL);
USE_STRING_ID(UDINT);
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

DEFINE_FIRMWARE_FB(FORTE_HMIProgressbar, STRID(HMIProgressbar))

const CStringDictionary::TStringId FORTE_HMIProgressbar::scmDataInputNames[] = {
    STRID(QI), STRID(Label), STRID(MinRange), STRID(MaxRange), STRID(WidgetName), STRID(IntegerOutput),
};
const CStringDictionary::TStringId FORTE_HMIProgressbar::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(UDINT), STRID(UDINT), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_HMIProgressbar::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIProgressbar::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIProgressbar::scmEIWith[] = {0, 1, 2, 3, 4, 5, scmWithListDelimiter};
const TForteInt16 FORTE_HMIProgressbar::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIProgressbar::scmIntegerOutputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMIProgressbar::scmIntegerOutputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMIProgressbar::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMIProgressbar::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMIProgressbar::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMIProgressbar::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMIProgressbar::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMIProgressbar::scmFBInterfaceSpec = {
    1,
    scmIntegerOutputNames,
    nullptr,
    scmEIWith,
    scmEIWithIndexes,
    2,
    scmEventOutputNames,
    nullptr,
    scmEOWith,
    scmEOWithIndexes,
    6,
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

const TForteUInt8 FORTE_HMIProgressbar::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMIProgressbar::scmSlaveConfigurationIONum = 0;

FORTE_HMIProgressbar::FORTE_HMIProgressbar(const CStringDictionary::TStringId paInstanceNameId,
                                           CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_MinRange(0_UDINT),
    var_MaxRange(100_UDINT),
    var_WidgetName(""_STRING),
    var_IntegerOutput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_MinRange(nullptr),
    conn_MaxRange(nullptr),
    conn_WidgetName(nullptr),
    conn_IntegerOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMIProgressbar::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_MinRange = 0_UDINT;
  var_MaxRange = 100_UDINT;
  var_WidgetName = ""_STRING;
  var_IntegerOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIProgressbar::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(5, var_IntegerOutput, conn_IntegerOutput);
      readData(4, var_WidgetName, conn_WidgetName);
      readData(1, var_Label, conn_Label);
      readData(2, var_MinRange, conn_MinRange);
      readData(3, var_MaxRange, conn_MaxRange);
      break;
    }
    default: break;
  }
}

void FORTE_HMIProgressbar::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIProgressbar::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_MinRange;
    case 3: return &var_MaxRange;
    case 4: return &var_WidgetName;
    case 5: return &var_IntegerOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIProgressbar::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIProgressbar::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIProgressbar::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_MinRange;
    case 3: return &conn_MaxRange;
    case 4: return &conn_WidgetName;
    case 5: return &conn_IntegerOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIProgressbar::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMIProgressbar::initHandles() {
  auto minRange = static_cast<TForteUInt32>(var_MinRange);
  auto maxRange = static_cast<TForteUInt32>(var_MaxRange);

  if (!std::in_range<int32_t>(minRange) || !std::in_range<int32_t>(maxRange)) {
    DEVLOG_WARNING("[FORTE_HMIProgressbar] MinRange or MaxRange is too large\n");
    // TODO: set status
    return;
  }

  lv_obj_t *widget = static_cast<HMIDeviceController &>(getController())
                         .getConnector()
                         .connectProgressbar(var_WidgetName.getStorage(), var_Label.getStorage(),
                                             static_cast<int32_t>(minRange), static_cast<int32_t>(maxRange));

  if (!widget) {
    // TODO: set status
    return;
  }

  HMIDeviceController::HMIBarValueHandleDescriptor desc(var_IntegerOutput.getStorage(), IOMapper::Out, 0,
                                                        CIEC_ANY::e_DWORD, widget);
  initHandle(desc);
}
