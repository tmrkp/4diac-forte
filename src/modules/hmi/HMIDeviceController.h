#pragma once

#include "HMIGenerator.h"
#include "io/device/io_controller_multi.h"
#include "lvgl/lvgl.h"

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
      PROGRESS_BAR,
      SLIDER,
      SUBJECT,
      SWITCH
    };

    class HMIHandleDescriptor : public HandleDescriptor {
      public:
        HMIHandleType mHandleType;
        std::string const &mName;
        std::string const *mLabel;
        std::string const *mOptions;

        HMIHandleDescriptor(std::string const &paId,
                            size_t paSlaveIndex,
                            HMIHandleType paHandleType,
                            std::string const &paName) :
            HandleDescriptor(paId, IOMapper::UnknownDirection, paSlaveIndex),
            mHandleType(paHandleType),
            mName(paName),
            mLabel(nullptr),
            mOptions(nullptr) {
        }

        HMIHandleDescriptor(std::string const &paId,
                            size_t paSlaveIndex,
                            HMIHandleType paHandleType,
                            std::string const &paName,
                            std::string const &paLabel) :
            HandleDescriptor(paId, IOMapper::UnknownDirection, paSlaveIndex),
            mHandleType(paHandleType),
            mName(paName),
            mLabel(&paLabel),
            mOptions(nullptr) {
        }

        HMIHandleDescriptor(std::string const &paId,
                            size_t paSlaveIndex,
                            HMIHandleType paHandleType,
                            std::string const &paName,
                            std::string const &paLabel,
                            std::string const &paOptions) :
            HandleDescriptor(paId, IOMapper::UnknownDirection, paSlaveIndex),
            mHandleType(paHandleType),
            mName(paName),
            mLabel(&paLabel),
            mOptions(&paOptions) {
        }
    };

    void setConfig(Config *paConfig) override;

    void addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) override;

    void dropSlaveHandles(size_t paIndex) override;

  protected:
    const char *init() override;

    IOHandle *createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) override;

    bool isHandleValueEqual(IOHandle &paHandle) override;

    void deInit() override;

    void runLoop() override;

    HMIConfig mConfig;

  private:
    HMIGenerator mGenerator;

    bool isSlaveAvailable(size_t paIndex) override;

    bool checkSlaveType(size_t paIndex, int paType) override;

    static lv_obj_t *findWidget(const std::string &paName, const lv_obj_class_t *paClass);

    static lv_subject_t *findSubject(const std::string &paName);

    template<typename T>
    IOHandle *createWidgetHandle(lv_obj_t *obj) {
      if (obj != nullptr) {
        return new T(this, obj);
      }
      return nullptr;
    }

    IOHandle *createSubjectHandle(lv_subject_t *subject);
};
