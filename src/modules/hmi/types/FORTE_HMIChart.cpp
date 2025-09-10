#include "FORTE_HMIChart.h"

#include "HMIDeviceController.h"

USE_STRING_ID(HMIChart);
USE_STRING_ID(QI);
USE_STRING_ID(Label);
USE_STRING_ID(MinYRange);
USE_STRING_ID(MaxYRange);
USE_STRING_ID(PointCount);
USE_STRING_ID(WidgetName);
USE_STRING_ID(IntegerOutput);
USE_STRING_ID(BOOL);
USE_STRING_ID(WSTRING);
USE_STRING_ID(STRING);
USE_STRING_ID(DINT);
USE_STRING_ID(UDINT);
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

DEFINE_FIRMWARE_FB(FORTE_HMIChart, STRID(HMIChart))

const CStringDictionary::TStringId FORTE_HMIChart::scmDataInputNames[] = {
    STRID(QI),         STRID(Label),      STRID(MinYRange),     STRID(MaxYRange),
    STRID(PointCount), STRID(WidgetName), STRID(IntegerOutput),
};
const CStringDictionary::TStringId FORTE_HMIChart::scmDataInputTypeIds[] = {
    STRID(BOOL), STRID(STRING), STRID(UDINT), STRID(DINT), STRID(DINT), STRID(STRING), STRID(STRING),
};
const CStringDictionary::TStringId FORTE_HMIChart::scmDataOutputNames[] = {STRID(QO), STRID(STATUS)};
const CStringDictionary::TStringId FORTE_HMIChart::scmDataOutputTypeIds[] = {STRID(BOOL), STRID(WSTRING)};
const TDataIOID FORTE_HMIChart::scmEIWith[] = {0, 1, 2, 3, 4, 5, 6, scmWithListDelimiter};
const TForteInt16 FORTE_HMIChart::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_HMIChart::scmIntegerOutputNames[] = {STRID(MAP)};
const CStringDictionary::TStringId FORTE_HMIChart::scmIntegerOutputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_HMIChart::scmEOWith[] = {0, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 FORTE_HMIChart::scmEOWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_HMIChart::scmEventOutputNames[] = {STRID(MAPO), STRID(IND)};
const CStringDictionary::TStringId FORTE_HMIChart::scmEventOutputTypeIds[] = {STRID(Event), STRID(Event)};
const SAdapterInstanceDef FORTE_HMIChart::scmAdapterInstances[] = {
    {STRID(HMIBusAdapter), STRID(BusAdapterOut), true},
    {STRID(HMIBusAdapter), STRID(BusAdapterIn), false},
};
const SFBInterfaceSpec FORTE_HMIChart::scmFBInterfaceSpec = {
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

const TForteUInt8 FORTE_HMIChart::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_HMIChart::scmSlaveConfigurationIONum = 0;

FORTE_HMIChart::FORTE_HMIChart(const CStringDictionary::TStringId paInstanceNameId, CFBContainer &paContainer) :
    IOConfigFBMultiSlave(
        scmSlaveConfigurationIO, scmSlaveConfigurationIONum, 0, paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_QI(0_BOOL),
    var_Label(""_STRING),
    var_MinYRange(0_UDINT),
    var_MaxYRange(100_UDINT),
    var_PointCount(0_UDINT),
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
    conn_MinYRange(nullptr),
    conn_MaxYRange(nullptr),
    conn_PointCount(nullptr),
    conn_WidgetName(nullptr),
    conn_IntegerOutput(nullptr),
    conn_QO(*this, 0, var_conn_QO),
    conn_STATUS(*this, 1, var_conn_STATUS) {
}

void FORTE_HMIChart::setInitialValues() {
  var_QI = 0_BOOL;
  var_Label = ""_STRING;
  var_MinYRange = 0_DINT;
  var_MaxYRange = 100_DINT;
  var_PointCount = 0_UDINT;
  var_WidgetName = ""_STRING;
  var_IntegerOutput = ""_STRING;
  var_QO = 0_BOOL;
  var_STATUS = u""_WSTRING;
}

void FORTE_HMIChart::readInputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPID: {
      readData(0, var_QI, conn_QI);
      readData(6, var_IntegerOutput, conn_IntegerOutput);
      readData(5, var_WidgetName, conn_WidgetName);
      readData(1, var_Label, conn_Label);
      readData(4, var_PointCount, conn_PointCount);
      readData(2, var_MinYRange, conn_MinYRange);
      readData(3, var_MaxYRange, conn_MaxYRange);
      break;
    }
    default: break;
  }
}

void FORTE_HMIChart::writeOutputData(const TEventID paEIID) {
  switch (paEIID) {
    case scmEventMAPOID: {
      writeData(0, var_QO, conn_QO);
      writeData(1, var_STATUS, conn_STATUS);
      break;
    }
    default: break;
  }
}

CIEC_ANY *FORTE_HMIChart::getDI(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QI;
    case 1: return &var_Label;
    case 2: return &var_MinYRange;
    case 3: return &var_MaxYRange;
    case 4: return &var_PointCount;
    case 5: return &var_WidgetName;
    case 6: return &var_IntegerOutput;
  }
  return nullptr;
}

CIEC_ANY *FORTE_HMIChart::getDO(const size_t paIndex) {
  switch (paIndex) {
    case 0: return &var_QO;
    case 1: return &var_STATUS;
  }
  return nullptr;
}

CEventConnection *FORTE_HMIChart::getEOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_MAPO;
    case 1: return &conn_IND;
  }
  return nullptr;
}

CDataConnection **FORTE_HMIChart::getDIConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QI;
    case 1: return &conn_Label;
    case 2: return &conn_MinYRange;
    case 3: return &conn_MaxYRange;
    case 4: return &conn_PointCount;
    case 5: return &conn_WidgetName;
    case 6: return &conn_IntegerOutput;
  }
  return nullptr;
}

CDataConnection *FORTE_HMIChart::getDOConUnchecked(const TPortId paIndex) {
  switch (paIndex) {
    case 0: return &conn_QO;
    case 1: return &conn_STATUS;
  }
  return nullptr;
}

void FORTE_HMIChart::initHandles() {
  auto minYRange = static_cast<TForteInt32>(var_MinYRange);
  auto maxYRange = static_cast<TForteInt32>(var_MaxYRange);
  auto pointCount = static_cast<TForteUInt32>(var_PointCount);

  lv_obj_t *widget =
      static_cast<HMIDeviceController &>(getController())
          .getConnector()
          .connectChart(var_WidgetName.getStorage(), var_Label.getStorage(), minYRange, maxYRange, pointCount);

  if (!widget) {
    return;
  }

  HMIDeviceController::HMIChartSeriesHandlerDescriptor desc(var_IntegerOutput.getStorage(), IOMapper::Out, 0,
                                                            CIEC_ANY::e_DWORD, widget);
  initHandle(desc);
}
