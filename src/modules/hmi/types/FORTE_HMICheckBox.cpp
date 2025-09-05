#include "FORTE_HMICheckBox.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMICheckBox);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(WidgetName);
USE_STRING_ID(CheckedBooleanInput);
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
USE_STRING_ID(HMIBusAdapter);
USE_STRING_ID(BusAdapterIn);
USE_STRING_ID(BusAdapterOut);
USE_STRING_ID(Event);

DEFINE_FIRMWARE_FB(FORTE_HMICheckBox, STRID(HMICheckBox))

const CStringDictionary::TStringId FORTE_HMICheckBox::scmDataInputNames[] = {
    STRID(QI), STRID(Label), STRID(WidgetName), STRID(CheckedBooleanInput), STRID(DisabledBooleanOutput)};
const CStringDictionary::TStringId FORTE_HMICheckBox::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(STRING), STRID(STRING), STRID(STRING)};
const CStringDictionary::TStringId FORTE_HMICheckBox::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMICheckBox::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMICheckBox::scmEIWith[] = {0, 1, 2, 3, 4, scmWithListDelimiter};
const TForteInt16 FORTE_HMICheckBox::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMICheckBox::scmBooleanInputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMICheckBox::scmBooleanInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMICheckBox::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMICheckBox::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMICheckBox::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMICheckBox::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMICheckBox::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMICheckBox::scmFBInterfaceSpec = {
    1,
    scmBooleanInputNames,
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

const TForteUInt8 FORTE_HMICheckBox::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMICheckBox::scmSlaveConfigurationIONum = 0;

FORTE_HMICheckBox::FORTE_HMICheckBox(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_WidgetName(""_STRING),
    var_CheckedBooleanInput(""_STRING),
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
    conn_CheckedBooleanInput(nullptr),
    conn_DisabledBooleanOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMICheckBox::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_WidgetName = ""_STRING;
  var_CheckedBooleanInput = ""_STRING;
  var_DisabledBooleanOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMICheckBox::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(1, var_Label, conn_Label);
      readData(2, var_WidgetName, conn_WidgetName);
      readData(3, var_CheckedBooleanInput, conn_CheckedBooleanInput);
      readData(4, var_DisabledBooleanOutput, conn_DisabledBooleanOutput);
      break;
    }
    default: break;
  }
}

void FORTE_HMICheckBox::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMICheckBox::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_WidgetName;
    case 3: return &var_CheckedBooleanInput;
    case 4: return &var_DisabledBooleanOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMICheckBox::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMICheckBox::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMICheckBox::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_WidgetName;
    case 3: return &conn_CheckedBooleanInput;
    case 4: return &conn_DisabledBooleanOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMICheckBox::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMICheckBox::initHandles() {
  HMIDeviceController::HMIWidgetStateHandleDescriptor checkedDesc(
      var_CheckedBooleanInput.getStorage(), IOMapper::In, 0, CIEC_ANY::e_BOOL, var_WidgetName.getStorage(),
      &lv_checkbox_class, LV_STATE_CHECKED, LV_EVENT_VALUE_CHANGED);
  initHandle(checkedDesc);

  HMIDeviceController::HMIWidgetStateHandleDescriptor disabledDesc(
      var_DisabledBooleanOutput.getStorage(), IOMapper::Out, 1, CIEC_ANY::e_BOOL, var_WidgetName.getStorage(),
      &lv_checkbox_class, LV_STATE_DISABLED, LV_EVENT_ALL);
  initHandle(disabledDesc);
}
