#include "FORTE_LVGLProgressbar.h"

#include "LVGLDeviceController.h"

USE_STRING_ID(LVGLProgressbar);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(MinRange);
USE_STRING_ID(MaxRange);
USE_STRING_ID(WidgetName);
USE_STRING_ID(IntegerOutput);
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

DEFINE_FIRMWARE_FB(FORTE_LVGLProgressbar, STRID(LVGLProgressbar))

const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmDataInputNames[] = {
    STRID(QI), STRID(Label), STRID(MinRange), STRID(MaxRange), STRID(WidgetName), STRID(IntegerOutput),
};
const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(DINT), STRID(DINT), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_LVGLProgressbar::scmEIWith[] = {0, 1, 2, 3, 4, 5, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLProgressbar::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmIntegerOutputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmIntegerOutputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLProgressbar::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLProgressbar::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_LVGLProgressbar::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_LVGLProgressbar::scmAdapterInstances[] = {
    {STRID(LVGLBusAdapter), STRID(BusAdapterOut), true},
    {STRID(LVGLBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_LVGLProgressbar::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_LVGLProgressbar::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_LVGLProgressbar::scmSlaveConfigurationIONum = 0;

FORTE_LVGLProgressbar::FORTE_LVGLProgressbar(const CStringDictionary::TStringId paInstanceNameId,
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

void FORTE_LVGLProgressbar::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_MinRange = 0_DINT;
  var_MaxRange = 100_DINT;
  var_WidgetName = ""_STRING;
  var_IntegerOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_LVGLProgressbar::readInputData(const TEventID paEIID) {
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

void FORTE_LVGLProgressbar::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_LVGLProgressbar::getDI(const size_t paIndex) {
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

CIEC_ANY *FORTE_LVGLProgressbar::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_LVGLProgressbar::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_LVGLProgressbar::getDIConUnchecked(const TPortId paIndex) {
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

CDataConnection *FORTE_LVGLProgressbar::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_LVGLProgressbar::initHandles() {
  auto minRange = static_cast<TForteInt32>(var_MinRange);
  auto maxRange = static_cast<TForteInt32>(var_MaxRange);

  lv_obj_t *widget = static_cast<LVGLDeviceController &>(getController())
                         .getConnector()
                         .connectProgressbar(var_WidgetName.getStorage(), var_Label.getStorage(), minRange, maxRange);

  if (!widget) {
    return;
  }

  LVGLDeviceController::LVGLBarValueHandleDescriptor desc(var_IntegerOutput.getStorage(), IOMapper::Out, 0,
                                                        CIEC_ANY::e_DWORD, widget);
  initHandle(desc);
}
