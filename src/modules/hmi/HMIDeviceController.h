#pragma once

#include "HMIGenerator.h"
#include "device/io_controller_multi.h"
#include "lvgl/lvgl.h"

#include "handles/HMIDropdownSelectedIndexHandle.h"
#include "handles/HMIWidgetStateHandle.h"
#include "handles/HMILEDBrightnessHandle.h"
#include "handles/HMISubjectHandle.h"
#include "handles/HMILabelTextHandle.h"

using namespace forte::core::io;

class HMIDeviceController : public IODeviceMultiController {
  public:
    explicit HMIDeviceController(CDeviceExecution &paDeviceExecution);

    ~HMIDeviceController() override = default;

    struct HMIConfig : Config {};

    enum HMIHandleType {
      BOOLEAN_INDICATOR,
      BUTTON,
      CHECK_BOX,
      DROP_DOWN,
      NUMBER,
      OBSERVER,
      PROGRESS_BAR,
      SLIDER,
      SPIN_BOX,
      SUBJECT,
      SWITCH
    };

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
                                   const std::string &paSubjectName) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mSubjectName(paSubjectName) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMISubjectHandle(paController, mDirection, findSubject(mSubjectName));
        }

      private:
        const std::string &mSubjectName;
    };

    class HMIWidgetStateHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMIWidgetStateHandleDescriptor(std::string const &paId,
                                       IOMapper::Direction paDirection,
                                       size_t paSlaveIndex,
                                       CIEC_ANY::EDataTypeID paType,
                                       const std::string &paWidgetName,
                                       const lv_obj_class_t *paClass,
                                       lv_state_t paState,
                                       lv_event_code_t paEventCode) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidgetName(paWidgetName),
            mClass(paClass),
            mState(paState),
            mEventCode(paEventCode) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMIWidgetStateHandle(paController, mDirection, mType, findWidget(mWidgetName, mClass), mState,
                                          mEventCode);
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        const std::string &mWidgetName;
        const lv_obj_class_t *mClass;
        lv_state_t mState;
        lv_event_code_t mEventCode;
    };

    class HMILEDBrightnessHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMILEDBrightnessHandleDescriptor(std::string const &paId,
                                         size_t paSlaveIndex,
                                         CIEC_ANY::EDataTypeID paType,
                                         const std::string &paWidgetName) :
            HMIHandleDescriptor(paId, IOMapper::Out, paSlaveIndex),
            mType(paType),
            mWidgetName(paWidgetName) {
        }

        IOHandle *createIOHandle(HMIDeviceController *controller) override {
          return new HMILEDBrightnessHandle(controller, mType, findWidget(mWidgetName, &lv_led_class));
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        const std::string &mWidgetName;
    };

    class HMIDropdownSelectedIndexHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMIDropdownSelectedIndexHandleDescriptor(std::string const &paId,
                                                 IOMapper::Direction paDirection,
                                                 size_t paSlaveIndex,
                                                 CIEC_ANY::EDataTypeID paType,
                                                 const std::string &paWidgetName) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidgetName(paWidgetName) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMIDropdownSelectedIndexHandle(paController, mDirection, mType,
                                                    findWidget(mWidgetName, &lv_dropdown_class));
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        const std::string &mWidgetName;
    };

    class HMINumberTextHandleDescriptor : public HMIHandleDescriptor {
      public:
        HMINumberTextHandleDescriptor(std::string const &paId,
                                      IOMapper::Direction paDirection,
                                      size_t paSlaveIndex,
                                      CIEC_ANY::EDataTypeID paType,
                                      const std::string &paWidgetName) :
            HMIHandleDescriptor(paId, paDirection, paSlaveIndex),
            mType(paType),
            mWidgetName(paWidgetName) {
        }

        IOHandle *createIOHandle(HMIDeviceController *paController) override {
          return new HMILabelTextHandle(paController, mDirection, mType, findWidget(mWidgetName, &lv_label_class),
                                        "%d");
        }

      private:
        CIEC_ANY::EDataTypeID mType;
        const std::string &mWidgetName;
    };

    void setConfig(Config *paConfig) override;

    void addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) override;

    void dropSlaveHandles(size_t paIndex) override;

  protected:
    const char *init() override;

    IOHandle *createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) override;

    void deInit() override;

    void runLoop() override;

    HMIConfig mConfig;

  private:
    HMIGenerator mGenerator;

    bool isSlaveAvailable(size_t paIndex) override;

    bool checkSlaveType(size_t paIndex, int paType) override;

    static lv_obj_t *findWidget(const std::string &paName, const lv_obj_class_t *paClass);

    static lv_subject_t *findSubject(const std::string &paName);
};
