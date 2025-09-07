#pragma once

#include "device/io_controller_multi.h"
#include "lvgl/lvgl.h"

#include "connector/HMIConnectorInterface.h"
#include "connector/HMIAutoUIConnector.h"
#include "handles/HMIDropdownSelectedIndexHandle.h"
#include "handles/HMIWidgetStateHandle.h"
#include "handles/HMILEDBrightnessHandle.h"
#include "handles/HMISubjectHandle.h"
#include "handles/HMILabelTextHandle.h"
#include "handles/HMISpinboxValueHandle.h"
#include "handles/HMISliderValueHandle.h"
#include "handles/HMIBarValueHandle.h"
#include "handles/HMIChartSeriesHandle.h"

using namespace forte::core::io;

class HMIDeviceController : public IODeviceMultiController {
  public:
    explicit HMIDeviceController(CDeviceExecution &paDeviceExecution);

    ~HMIDeviceController() override = default;

    struct HMIConfig : Config {};

    class HMIHandleDescriptor : public HandleDescriptor {
      public:
        HMIHandleDescriptor(std::string const &paId, IOMapper::Direction paDirection, size_t paSlaveIndex) :
            HandleDescriptor(paId, paDirection, paSlaveIndex) {
        }
        virtual ~HMIHandleDescriptor() = default;

        virtual IOHandle *createIOHandle(HMIDeviceController *controller) = 0;
    };

    class HMISubjectHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMISubjectHandleDescriptor(std::string const &paId,
                                   IOMapper::Direction paDirection,
                                   size_t paSlaveIndex,
                                   lv_subject_t *paSubject) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mSubject(paSubject) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMISubjectHandle(paController, mDirection, mSubject);
        }

      private:
        lv_subject_t *mSubject;
    };

    class HMIWidgetStateHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMIWidgetStateHandleDescriptor(std::string const &paId,
                                       IOMapper::Direction paDirection,
                                       size_t paSlaveIndex,
                                       CIEC_ANY::EDataTypeID paType,
                                       lv_obj_t *paWidget,
                                       lv_state_t paState,
                                       lv_event_code_t paEventCode) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget),
            mState(paState),
            mEventCode(paEventCode) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMIWidgetStateHandle(paController, mDirection, mType, mWidget, mState, mEventCode);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
        lv_state_t mState;
        lv_event_code_t mEventCode;
    };

    class HMILEDBrightnessHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMILEDBrightnessHandleDescriptor(std::string const &paId,
                                         size_t paSlaveIndex,
                                         CIEC_ANY::EDataTypeID paType,
                                         lv_obj_t *paWidget) :
            HMIHandleDescriptor(paId, IOMapper::Out, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(HMIDeviceController *controller) override {
          return new HMILEDBrightnessHandle(controller, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class HMIDropdownSelectedIndexHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMIDropdownSelectedIndexHandleDescriptor(std::string const &paId,
                                                 IOMapper::Direction paDirection,
                                                 size_t paSlaveIndex,
                                                 CIEC_ANY::EDataTypeID paType,
                                                 lv_obj_t *paWidget) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMIDropdownSelectedIndexHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class HMINumberTextHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMINumberTextHandleDescriptor(std::string const &paId,
                                      IOMapper::Direction paDirection,
                                      size_t paSlaveIndex,
                                      CIEC_ANY::EDataTypeID paType,
                                      lv_obj_t *paWidget) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMILabelTextHandle(paController, mDirection, mType, mWidget, "%d");
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class HMISpinboxValueHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMISpinboxValueHandleDescriptor(std::string const &paId,
                                        IOMapper::Direction paDirection,
                                        size_t paSlaveIndex,
                                        CIEC_ANY::EDataTypeID paType,
                                        lv_obj_t *paWidget) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMISpinboxValueHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class HMISliderValueHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMISliderValueHandleDescriptor(std::string const &paId,
                                       IOMapper::Direction paDirection,
                                       size_t paSlaveIndex,
                                       CIEC_ANY::EDataTypeID paType,
                                       lv_obj_t *paWidget,
                                       lv_event_code_t paEventCode) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget),
            mEventCode(paEventCode) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMISliderValueHandle(paController, mDirection, mType, mWidget, mEventCode);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
        lv_event_code_t mEventCode;
    };

    class HMIBarValueHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMIBarValueHandleDescriptor(std::string const &paId,
                                    IOMapper::Direction paDirection,
                                    size_t paSlaveIndex,
                                    CIEC_ANY::EDataTypeID paType,
                                    lv_obj_t *paWidget) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMIBarValueHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class HMIChartSeriesHandlerDescriptor : public HMIHandleDescriptor {
      public:
        HMIChartSeriesHandlerDescriptor(std::string const &paId,
                                        IOMapper::Direction paDirection,
                                        size_t paSlaveIndex,
                                        CIEC_ANY::EDataTypeID paType,
                                        lv_obj_t *paWidget) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMIChartSeriesHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    void setConfig(Config *paConfig) override;

    void addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) override;

    void dropSlaveHandles(size_t paIndex) override;

    HMIConnectorInterface &getConnector() {
      return mConnector;
    }

  protected:
    const char *init() override;

    IOHandle *createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) override;

    void deInit() override;

    void runLoop() override;

    HMIConfig mConfig;

  private:
    HMIAutoUIConnector mConnector;

    bool isSlaveAvailable(size_t paIndex) override;

    bool checkSlaveType(size_t paIndex, int paType) override;
};
