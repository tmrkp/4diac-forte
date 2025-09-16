#include "FORTE_LVGLLED.h"

#include "LVGLDeviceController.h"

USE_STRING_ID(LVGLLED);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(BooleanOutput);
USE_STRING_ID(ByteOutput);
USE_STRING_ID(BOOL);
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

DEFINE_FIRMWARE_FB(FORTE_LVGLLED, STRID(LVGLLED))

const CStringDictionary::TStringId FORTE_LVGLLED::scmDataInputNames[] = {STRID(QI), STRID(Label), STRID(WidgetName),
                                                                        STRID(BooleanOutput), STRID(ByteOutput)};
const CStringDictionary::TStringId FORTE_LVGLLED::scmDataInputTypeIds[] = {STRID(BOOL), STRID(STRING), STRID(STRING),
                                                                          STRID(STRING), STRID(STRING)};
const CStringDictionary::TStringId FORTE_LVGLLED::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_LVGLLED::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_LVGLLED::scmEIWith[] = {0, 1, 2, 3, 4, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLLED::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLLED::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_LVGLLED::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLLED::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLLED::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_LVGLLED::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_LVGLLED::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_LVGLLED::scmAdapterInstances[] = {
    {STRID(LVGLBusAdapter), STRID(BusAdapterOut), true},
    {STRID(LVGLBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_LVGLLED::scmFBInterfaceSpec = {
    1,
    scmEventInputNames,
    nullptr,
    scmEIWith,
    scmEIWithIndexes,
    2,
    scmEventOutputNames,
    nullptr,
    scmEOWith,
    scmEOWithIndexes,
    5,
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

const TForteUInt8 FORTE_LVGLLED::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_LVGLLED::scmSlaveConfigurationIONum = 0;

FORTE_LVGLLED::FORTE_LVGLLED(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_BooleanOutput(""_STRING),
    var_ByteOutput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_WidgetName(nullptr),
    conn_BooleanOutput(nullptr),
    conn_ByteOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_LVGLLED::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_BooleanOutput = ""_STRING;
  var_ByteOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_LVGLLED::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_BooleanOutput, conn_BooleanOutput);
      readData(4, var_ByteOutput, conn_ByteOutput);
      break;
    }
    default: break;
  }
}

void FORTE_LVGLLED::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_LVGLLED::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_BooleanOutput;
    case 4: return &var_ByteOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LVGLLED::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_LVGLLED::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_LVGLLED::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_BooleanOutput;
    case 4: return &conn_ByteOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_LVGLLED::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_LVGLLED::initHandles() {
  lv_obj_t *widget = static_cast<LVGLDeviceController &>(getController())
                         .getConnector()
                         .connectLED(var_WidgetName.getStorage(), var_Label.getStorage());

  if (!widget) {
    return;
  }

  LVGLDeviceController::LVGLLEDBrightnessHandleDescriptor boolDesc(var_BooleanOutput.getStorage(), 0, CIEC_ANY::e_BOOL,
                                                                 widget);
  initHandle(boolDesc);
  LVGLDeviceController::LVGLLEDBrightnessHandleDescriptor byteDesc(var_ByteOutput.getStorage(), 1, CIEC_ANY::e_BYTE,
                                                                 widget);
  initHandle(byteDesc);
}
