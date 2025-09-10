#include "FORTE_HMIButton.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMIButton);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(PressedEventInput);
USE_STRING_ID(ReleasedEventInput);
USE_STRING_ID(LongPressedEventInput);
USE_STRING_ID(DoubleClickedEventInput);
USE_STRING_ID(BOOL);
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

DEFINE_FIRMWARE_FB(FORTE_HMIButton, STRID(HMIButton))

const CStringDictionary::TStringId FORTE_HMIButton::scmDataInputNames[] = {
    STRID(QI),
    STRID(Label),
    STRID(WidgetName),
    STRID(PressedEventInput),
    STRID(ReleasedEventInput),
    STRID(LongPressedEventInput),
    STRID(DoubleClickedEventInput),
};
const CStringDictionary::TStringId FORTE_HMIButton::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(STRING), STRID(STRING), STRID(STRING), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_HMIButton::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIButton::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIButton::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, scmWithListDelimiter};
const TForteInt16 FORTE_HMIButton::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMIButton::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMIButton::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMIButton::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMIButton::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMIButton::scmFBInterfaceSpec = {
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
    7,
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

const TForteUInt8 FORTE_HMIButton::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMIButton::scmSlaveConfigurationIONum = 0;

FORTE_HMIButton::FORTE_HMIButton(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_PressedEventInput(""_STRING),
    var_ReleasedEventInput(""_STRING),
    var_LongPressedEventInput(""_STRING),
    var_DoubleClickedEventInput(""_STRING),
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
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMIButton::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_PressedEventInput = ""_STRING;
  var_ReleasedEventInput = ""_STRING;
  var_LongPressedEventInput = ""_STRING;
  var_DoubleClickedEventInput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIButton::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_PressedEventInput, conn_PressedEventInput);
      readData(4, var_ReleasedEventInput, conn_ReleasedEventInput);
      readData(5, var_LongPressedEventInput, conn_LongPressedEventInput);
      readData(6, var_DoubleClickedEventInput, conn_DoubleClickedEventInput);
      break;
    }
    default: break;
  }
}

void FORTE_HMIButton::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIButton::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_PressedEventInput;
    case 4: return &var_ReleasedEventInput;
    case 5: return &var_LongPressedEventInput;
    case 6: return &var_DoubleClickedEventInput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIButton::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIButton::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIButton::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_PressedEventInput;
    case 4: return &conn_ReleasedEventInput;
    case 5: return &conn_LongPressedEventInput;
    case 6: return &conn_DoubleClickedEventInput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIButton::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMIButton::initHandles() {
  lv_obj_t *widget = static_cast<HMIDeviceController &>(getController())
                         .getConnector()
                         .connectButton(var_WidgetName.getStorage(), var_Label.getStorage());

  if (!widget) {
    return;
  }

  HMIDeviceController::HMIWidgetStateHandleDescriptor pressed(var_PressedEventInput.getStorage(), IOMapper::In, 0,
                                                              CIEC_ANY::e_Max, widget, LV_STATE_ANY, LV_EVENT_PRESSED);
  initHandle(pressed);
  HMIDeviceController::HMIWidgetStateHandleDescriptor released(
      var_ReleasedEventInput.getStorage(), IOMapper::In, 1, CIEC_ANY::e_Max, widget, LV_STATE_ANY, LV_EVENT_RELEASED);
  initHandle(released);
  HMIDeviceController::HMIWidgetStateHandleDescriptor longPressed(var_LongPressedEventInput.getStorage(), IOMapper::In,
                                                                  2, CIEC_ANY::e_Max, widget, LV_STATE_ANY,
                                                                  LV_EVENT_LONG_PRESSED);
  initHandle(longPressed);
  HMIDeviceController::HMIWidgetStateHandleDescriptor doubleClickedEventDesc(var_DoubleClickedEventInput.getStorage(),
                                                                             IOMapper::In, 3, CIEC_ANY::e_Max, widget,
                                                                             LV_STATE_ANY, LV_EVENT_DOUBLE_CLICKED);
  initHandle(doubleClickedEventDesc);
}
