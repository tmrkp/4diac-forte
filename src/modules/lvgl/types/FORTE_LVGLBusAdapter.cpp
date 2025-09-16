#include "FORTE_LVGLBusAdapter.h"

USE_STRING_ID(BOOL);
USE_STRING_ID(Event);
USE_STRING_ID(Index);
USE_STRING_ID(INIT);
USE_STRING_ID(INITO);
USE_STRING_ID(MasterId);
USE_STRING_ID(QI);
USE_STRING_ID(QO);
USE_STRING_ID(UINT);
USE_STRING_ID(LVGLBusAdapter);

DEFINE_ADAPTER_TYPE(FORTE_LVGLBusAdapter, STRID(LVGLBusAdapter))

const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmDataInputNames[] = {STRID(QO)};
const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmDataInputTypeIds[] = {STRID(BOOL)};
const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmDataOutputNames[] = {
    STRID(QI), STRID(MasterId), STRID(Index)};
const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmDataOutputTypeIds[] = {
    STRID(BOOL), STRID(UINT), STRID(UINT)};
const TDataIOID FORTE_LVGLBusAdapter::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLBusAdapter::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmEventInputNames[] = {STRID(INITO)};
const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmEventInputTypeIds[] = {STRID(Event)};
const TDataIOID FORTE_LVGLBusAdapter::scmEOWith[] = {0, 1, 2, scmWithListDelimiter};
const TForteInt16 FORTE_LVGLBusAdapter::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmEventOutputNames[] = {STRID(INIT)};
const CStringDictionary::TStringId FORTE_LVGLBusAdapter::scmEventOutputTypeIds[] = {STRID(Event)};

const SFBInterfaceSpec FORTE_LVGLBusAdapter::scmFBInterfaceSpecSocket = {
    1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
    1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
    1, scmDataInputNames, scmDataInputTypeIds,
    3, scmDataOutputNames, scmDataOutputTypeIds,
    0, nullptr,
    0, nullptr
};

const SFBInterfaceSpec FORTE_LVGLBusAdapter::scmFBInterfaceSpecPlug = {
    1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
    1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
    3, scmDataOutputNames, scmDataOutputTypeIds,
    1, scmDataInputNames, scmDataInputTypeIds,
    0, nullptr,
    0, nullptr
};

void FORTE_LVGLBusAdapter::readInputData(const TEventID paEIID) {
  if (isSocket()) {
    switch (paEIID) {
      case scmEventINITOID: {
        readData(0, *mDIs[0], mDIConns[0]);
        break;
      }
      default: break;
    }
  } else {
    switch (paEIID) {
      case scmEventINITID: {
        readData(0, *mDIs[0], mDIConns[0]);
        readData(1, *mDIs[1], mDIConns[1]);
        readData(2, *mDIs[2], mDIConns[2]);
        break;
      }
      default: break;
    }
  }
}

void FORTE_LVGLBusAdapter::writeOutputData(const TEventID paEIID) {
  if (isSocket()) {
    switch (paEIID) {
      case scmEventINITID: {
        writeData(0, *mDOs[0], mDOConns[0]);
        writeData(1, *mDOs[1], mDOConns[1]);
        writeData(2, *mDOs[2], mDOConns[2]);
        break;
      }
      default: break;
    }
  } else {
    switch (paEIID) {
      case scmEventINITOID: {
        writeData(0, *mDOs[0], mDOConns[0]);
        break;
      }
      default: break;
    }
  }
}

const TForteUInt8 FORTE_LVGLBusAdapter::scmSlaveConfigurationIO[] = {};
const TForteUInt8 FORTE_LVGLBusAdapter::scmSlaveConfigurationIONum = 0;
