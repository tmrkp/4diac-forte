#include "FORTE_LVGLButton.h"

#include "LVGLDeviceController.h"

USE_STRING_ID(LVGLButton);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(PressedEventInput);
USE_STRING_ID(ReleasedEventInput);
USE_STRING_ID(LongPressedEventInput);
USE_STRING_ID(DoubleClickedEventInput);
USE_STRING_ID(DisabledBooleanOutput);
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

DEFINE_FIRMWARE_FB(FORTE_LVGLButton, STRID(LVGLButton))

const CStringDictionary::TStringId FORTE_LVGLButton::scmDataInputNames[] = {
    STRID(QI),
    STRID(Label),
    STRID(WidgetName),
    STRID(PressedEventInput),
    STRID(ReleasedEventInput),
    STRID(LongPressedEventInput),
    STRID(DoubleClickedEventInput),
    STRID(DisabledBooleanOutput),
};
const CStringDictionary::TStringId FORTE_LVGLButton::scmDataInputTypeIds[] = {
    STRID(BOOL),   STRID(STRING), STRID(STRING), STRID(STRING),
    STRID(STRING), STRID(STRING), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_LVGLButton::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_LVGLButton::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_LVGLButton::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, 7, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLButton::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLButton::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_LVGLButton::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLButton::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLButton::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_LVGLButton::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_LVGLButton::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_LVGLButton::scmAdapterInstances[] = {
    {STRID(LVGLBusAdapter), STRID(BusAdapterOut), true},
    {STRID(LVGLBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_LVGLButton::scmFBInterfaceSpec = {
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
    8,
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

const TForteUInt8 FORTE_LVGLButton::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_LVGLButton::scmSlaveConfigurationIONum = 0;

FORTE_LVGLButton::FORTE_LVGLButton(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_PressedEventInput(""_STRING),
    var_ReleasedEventInput(""_STRING),
    var_LongPressedEventInput(""_STRING),
    var_DoubleClickedEventInput(""_STRING),
    var_DisabledBooleanOutput(""_STRING),
    var_QO(0_BOOL),
    var_STATUS(u""_WSTRING),
    var_conn_QO(var_QO),
    var_conn_STATUS(var_STATUS),
    conn_MAPO(*this, 0),
    conn_IND(*this, 1),
    conn_QI(nullptr),
    conn_Label(nullptr),
    conn_WidgetName(nullptr),
    conn_PressedEventInput(nullptr),
    conn_ReleasedEventInput(nullptr),
    conn_LongPressedEventInput(nullptr),
    conn_DoubleClickedEventInput(nullptr),
    conn_DisabledBooleanOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_LVGLButton::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_PressedEventInput = ""_STRING;
  var_ReleasedEventInput = ""_STRING;
  var_LongPressedEventInput = ""_STRING;
  var_DoubleClickedEventInput = ""_STRING;
  var_DisabledBooleanOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_LVGLButton::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_PressedEventInput, conn_PressedEventInput);
      readData(4, var_ReleasedEventInput, conn_ReleasedEventInput);
      readData(5, var_LongPressedEventInput, conn_LongPressedEventInput);
      readData(6, var_DoubleClickedEventInput, conn_DoubleClickedEventInput);
      readData(7, var_DisabledBooleanOutput, conn_DisabledBooleanOutput);
      break;
    }
    default: break;
  }
}

void FORTE_LVGLButton::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_LVGLButton::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_PressedEventInput;
    case 4: return &var_ReleasedEventInput;
    case 5: return &var_LongPressedEventInput;
    case 6: return &var_DoubleClickedEventInput;
    case 7: return &var_DisabledBooleanOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_LVGLButton::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_LVGLButton::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_LVGLButton::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_PressedEventInput;
    case 4: return &conn_ReleasedEventInput;
    case 5: return &conn_LongPressedEventInput;
    case 6: return &conn_DoubleClickedEventInput;
    case 7: return &conn_DisabledBooleanOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_LVGLButton::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_LVGLButton::initHandles() {
  lv_obj_t *widget = static_cast<LVGLDeviceController &>(getController())
                         .getConnector()
                         .connectButton(var_WidgetName.getStorage(), var_Label.getStorage());

  if (!widget) {
    return;
  }

  LVGLDeviceController::LVGLWidgetStateHandleDescriptor pressed(
      var_PressedEventInput.getStorage(), IOMapper::In, 0, CIEC_ANY::e_Max, widget, LV_STATE_ANY, LV_EVENT_PRESSED);
  initHandle(pressed);
  LVGLDeviceController::LVGLWidgetStateHandleDescriptor released(
      var_ReleasedEventInput.getStorage(), IOMapper::In, 1, CIEC_ANY::e_Max, widget, LV_STATE_ANY, LV_EVENT_RELEASED);
  initHandle(released);
  LVGLDeviceController::LVGLWidgetStateHandleDescriptor longPressed(var_LongPressedEventInput.getStorage(),
                                                                    IOMapper::In, 2, CIEC_ANY::e_Max, widget,
                                                                    LV_STATE_ANY, LV_EVENT_LONG_PRESSED);
  initHandle(longPressed);
  LVGLDeviceController::LVGLWidgetStateHandleDescriptor doubleClickedEventDesc(var_DoubleClickedEventInput.getStorage(),
                                                                               IOMapper::In, 3, CIEC_ANY::e_Max, widget,
                                                                               LV_STATE_ANY, LV_EVENT_DOUBLE_CLICKED);
  initHandle(doubleClickedEventDesc);
  LVGLDeviceController::LVGLWidgetStateHandleDescriptor disabled(var_DisabledBooleanOutput.getStorage(), IOMapper::Out,
                                                                 4, CIEC_ANY::e_BOOL, widget, LV_STATE_DISABLED,
                                                                 LV_EVENT_ALL);
  initHandle(disabled);
}
