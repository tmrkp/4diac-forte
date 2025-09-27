#pragma once

#include "device/io_controller_multi.h"
#include "lvgl/lvgl.h"

#include "connector/LVGLConnectorInterface.h"
#include "connector/LVGLAutoUIConnector.h"
#include "handles/LVGLDropdownSelectedIndexHandle.h"
#include "handles/LVGLWidgetStateHandle.h"
#include "handles/LVGLLEDBrightnessHandle.h"
#include "handles/LVGLSubjectHandle.h"
#include "handles/LVGLNumberTextHandle.h"
#include "handles/LVGLSpinboxValueHandle.h"
#include "handles/LVGLSliderValueHandle.h"
#include "handles/LVGLBarValueHandle.h"
#include "handles/LVGLChartSeriesHandle.h"

using namespace forte::core::io;

class LVGLDeviceController : public IODeviceMultiController {
  public:
    explicit LVGLDeviceController(CDeviceExecution &paDeviceExecution);

    ~LVGLDeviceController() override = default;

    struct LVGLConfig : Config {};

    class LVGLHandleDescriptor : public HandleDescriptor {
      public:
        LVGLHandleDescriptor(std::string const &paId, IOMapper::Direction paDirection, size_t paSlaveIndex) :
            HandleDescriptor(paId, paDirection, paSlaveIndex) {
        }
        virtual ~LVGLHandleDescriptor() = default;

        virtual IOHandle *createIOHandle(LVGLDeviceController *controller) = 0;
    };

    class LVGLSubjectHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLSubjectHandleDescriptor(std::string const &paId,
                                    IOMapper::Direction paDirection,
                                    size_t paSlaveIndex,
                                    lv_subject_t *paSubject) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mSubject(paSubject) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLSubjectHandle(paController, mDirection, mSubject);
        }

      private:
        lv_subject_t *mSubject;
    };

    class LVGLWidgetStateHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLWidgetStateHandleDescriptor(std::string const &paId,
                                        IOMapper::Direction paDirection,
                                        size_t paSlaveIndex,
                                        CIEC_ANY::EDataTypeID paType,
                                        lv_obj_t *paWidget,
                                        lv_state_t paState,
                                        lv_event_code_t paEventCode) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget),
            mState(paState),
            mEventCode(paEventCode) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLWidgetStateHandle(paController, mDirection, mType, mWidget, mState, mEventCode);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
        lv_state_t mState;
        lv_event_code_t mEventCode;
    };

    class LVGLLEDBrightnessHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLLEDBrightnessHandleDescriptor(std::string const &paId,
                                          size_t paSlaveIndex,
                                          CIEC_ANY::EDataTypeID paType,
                                          lv_obj_t *paWidget) :
            LVGLHandleDescriptor(paId, IOMapper::Out, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *controller) override {
          return new LVGLLEDBrightnessHandle(controller, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class LVGLDropdownSelectedIndexHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLDropdownSelectedIndexHandleDescriptor(std::string const &paId,
                                                  IOMapper::Direction paDirection,
                                                  size_t paSlaveIndex,
                                                  CIEC_ANY::EDataTypeID paType,
                                                  lv_obj_t *paWidget) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLDropdownSelectedIndexHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class LVGLNumberTextHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLNumberTextHandleDescriptor(std::string const &paId,
                                       IOMapper::Direction paDirection,
                                       size_t paSlaveIndex,
                                       CIEC_ANY::EDataTypeID paType,
                                       lv_obj_t *paWidget) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLNumberTextHandle(paController, mDirection, mType, mWidget, "%d");
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class LVGLSpinboxValueHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLSpinboxValueHandleDescriptor(std::string const &paId,
                                         IOMapper::Direction paDirection,
                                         size_t paSlaveIndex,
                                         CIEC_ANY::EDataTypeID paType,
                                         lv_obj_t *paWidget) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLSpinboxValueHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class LVGLSliderValueHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLSliderValueHandleDescriptor(std::string const &paId,
                                        IOMapper::Direction paDirection,
                                        size_t paSlaveIndex,
                                        CIEC_ANY::EDataTypeID paType,
                                        lv_obj_t *paWidget,
                                        lv_event_code_t paEventCode) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget),
            mEventCode(paEventCode) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLSliderValueHandle(paController, mDirection, mType, mWidget, mEventCode);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
        lv_event_code_t mEventCode;
    };

    class LVGLBarValueHandleDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLBarValueHandleDescriptor(std::string const &paId,
                                     IOMapper::Direction paDirection,
                                     size_t paSlaveIndex,
                                     CIEC_ANY::EDataTypeID paType,
                                     lv_obj_t *paWidget) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLBarValueHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    class LVGLChartSeriesHandlerDescriptor : public LVGLHandleDescriptor {
      public:
        LVGLChartSeriesHandlerDescriptor(std::string const &paId,
                                         IOMapper::Direction paDirection,
                                         size_t paSlaveIndex,
                                         CIEC_ANY::EDataTypeID paType,
                                         lv_obj_t *paWidget) :
            LVGLHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidget(paWidget) {
        }

        IOHandle *createIOHandle(LVGLDeviceController *paController) override {
          return new LVGLChartSeriesHandle(paController, mDirection, mType, mWidget);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        lv_obj_t *mWidget;
    };

    void setConfig(Config *paConfig) override;

    void addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) override;

    void dropSlaveHandles(size_t paIndex) override;

    LVGLConnectorInterface &getConnector() {
      return mConnector;
    }

    void runLater(std::function<void()> task);

  protected:
    const char *init() override;

    IOHandle *createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) override;

    void deInit() override;

    void runLoop() override;

    LVGLConfig mConfig;

  private:
    LVGLAutoUIConnector mConnector;

    bool isSlaveAvailable(size_t paIndex) override;

    bool checkSlaveType(size_t paIndex, int paType) override;
};
