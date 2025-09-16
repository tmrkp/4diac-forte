#include "FORTE_LVGLSpinbox.h"

#include "LVGLDeviceController.h"

USE_STRING_ID(LVGLSpinbox);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(MinRange);
USE_STRING_ID(MaxRange);
USE_STRING_ID(WidgetName);
USE_STRING_ID(IntegerInput);
USE_STRING_ID(BOOL);
USE_STRING_ID(DINT);
USE_STRING_ID(WSTRING);
USE_STRING_ID(STRING);
USE_STRING_ID(QO);
USE_STRING_ID(STATUS);
USE_STRING_ID(MAP);
USE_STRING_ID(MAPO);
USE_STRING_ID(IND);
USE_STRING_ID(IND);
USE_STRING_ID(LVGLBusAdapter);
USE_STRING_ID(BusAdapterIn);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(Event);

DEFINE_FIRMWARE_FB(FORTE_LVGLSpinbox, STRID(LVGLSpinbox))

const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmDataInputNames[] = {
    STRID(QI), STRID(Label), STRID(MinRange), STRID(MaxRange), STRID(WidgetName), STRID(IntegerInput),
};
const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(DINT), STRID(DINT), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_LVGLSpinbox::scmEIWith[] = {0, 1, 2, 3, 4, 5, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLSpinbox::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmIntegerInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmIntegerInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLSpinbox::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLSpinbox::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_LVGLSpinbox::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_LVGLSpinbox::scmAdapterInstances[] = {
    {STRID(LVGLBusAdapter), STRID(BusAdapterOut), true},
    {STRID(LVGLBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_LVGLSpinbox::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_LVGLSpinbox::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_LVGLSpinbox::scmSlaveConfigurationIONum = 0;

FORTE_LVGLSpinbox::FORTE_LVGLSpinbox(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
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

void FORTE_LVGLSpinbox::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_MinRange = 0_DINT;
  var_MaxRange = 100_DINT;
  var_WidgetName = ""_STRING;
  var_IntegerInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_LVGLSpinbox::readInputData(const TEventID paEIID) {
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

void FORTE_LVGLSpinbox::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_LVGLSpinbox::getDI(const size_t paIndex) {
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

CIEC_ANY *FORTE_LVGLSpinbox::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_LVGLSpinbox::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_LVGLSpinbox::getDIConUnchecked(const TPortId paIndex) {
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

CDataConnection *FORTE_LVGLSpinbox::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_LVGLSpinbox::initHandles() {
  auto minRange = static_cast<TForteInt32>(var_MinRange);
  auto maxRange = static_cast<TForteInt32>(var_MaxRange);

  lv_obj_t *widget = static_cast<LVGLDeviceController &>(getController())
                         .getConnector()
                         .connectSpinbox(var_WidgetName.getStorage(), var_Label.getStorage(), minRange, maxRange);

  if (!widget) {
    return;
  }

  LVGLDeviceController::LVGLSpinboxValueHandleDescriptor desc(var_IntegerInput.getStorage(), IOMapper::In, 0,
                                                            CIEC_ANY::e_DWORD, widget);
  initHandle(desc);
}
