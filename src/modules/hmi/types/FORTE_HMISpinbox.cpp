#include "FORTE_HMISpinbox.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMISpinbox);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(MinRange);
USE_STRING_ID(MaxRange);
USE_STRING_ID(WidgetName);
USE_STRING_ID(IntegerInput);
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

DEFINE_FIRMWARE_FB(FORTE_HMISpinbox, STRID(HMISpinbox))

const CStringDictionary::TStringId FORTE_HMISpinbox::scmDataInputNames[] = {
    STRID(QI), STRID(Label), STRID(MinRange), STRID(MaxRange), STRID(WidgetName), STRID(IntegerInput),
};
const CStringDictionary::TStringId FORTE_HMISpinbox::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(UDINT), STRID(UDINT), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_HMISpinbox::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMISpinbox::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMISpinbox::scmEIWith[] = {0, 1, 2, 3, 4, 5, scmWithListDelimiter};
const TForteInt16 FORTE_HMISpinbox::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMISpinbox::scmIntegerInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMISpinbox::scmIntegerInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMISpinbox::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMISpinbox::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMISpinbox::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMISpinbox::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMISpinbox::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMISpinbox::scmFBInterfaceSpec = {
    1,
    scmIntegerInputNames,
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

const TForteUInt8 FORTE_HMISpinbox::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMISpinbox::scmSlaveConfigurationIONum = 0;

FORTE_HMISpinbox::FORTE_HMISpinbox(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_MinRange(0_UDINT),
    var_MaxRange(100_UDINT),
    var_WidgetName(""_STRING),
    var_IntegerInput(""_STRING),
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
    conn_IntegerInput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMISpinbox::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_MinRange = 0_UDINT;
  var_MaxRange = 100_UDINT;
  var_WidgetName = ""_STRING;
  var_IntegerInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMISpinbox::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_MinRange, conn_MinRange);
      readData(3, var_MaxRange, conn_MaxRange);
      readData(4, var_WidgetName, conn_WidgetName);
      readData(5, var_IntegerInput, conn_IntegerInput);
      break;
    }
    default: break;
  }
}

void FORTE_HMISpinbox::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMISpinbox::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_MinRange;
    case 3: return &var_MaxRange;
    case 4: return &var_WidgetName;
    case 5: return &var_IntegerInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMISpinbox::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMISpinbox::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMISpinbox::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_MinRange;
    case 3: return &conn_MaxRange;
    case 4: return &conn_WidgetName;
    case 5: return &conn_IntegerInput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMISpinbox::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMISpinbox::initHandles() {
  auto minRange = static_cast<TForteUInt32>(var_MinRange);
  auto maxRange = static_cast<TForteUInt32>(var_MaxRange);

  if (!std::in_range<int32_t>(minRange) || !std::in_range<int32_t>(maxRange)) {
    DEVLOG_WARNING("[FORTE_HMISpinbox] MinRange or MaxRange is too large\n");
    // TODO: set status
    return;
  }

  lv_obj_t *widget = static_cast<HMIDeviceController &>(getController())
                         .getConnector()
                         .connectSpinbox(var_WidgetName.getStorage(), var_Label.getStorage(),
                                         static_cast<int32_t>(minRange), static_cast<int32_t>(maxRange));

  if (!widget) {
    // TODO: set status
    return;
  }

  HMIDeviceController::HMISpinboxValueHandleDescriptor desc(var_IntegerInput.getStorage(), IOMapper::In, 0,
                                                            CIEC_ANY::e_DWORD, widget);
  initHandle(desc);
}
