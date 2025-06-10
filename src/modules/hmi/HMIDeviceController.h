#ifndef SRC_MODULES_HMI_MODULAR_HMIDEVICECONTROLLER_H_
#define SRC_MODULES_HMI_MODULAR_HMIDEVICECONTROLLER_H_

#include "io/device/io_controller_multi.h"

using namespace forte::core::io;

class HMIDeviceController : public IODeviceMultiController {
  public:
    explicit HMIDeviceController(CDeviceExecution &paDeviceExecution);

    ~HMIDeviceController() override;

    struct HMIConfig : Config {

    };

    class HMIHandleDescriptor : public HandleDescriptor {
      public:
        CIEC_ANY::EDataTypeID mType;

        HMIHandleDescriptor(std::string const &paId,
                            IOMapper::Direction paDirection,
                            size_t paSlaveIndex,
                            CIEC_ANY::EDataTypeID paType) :
          HandleDescriptor(paId, paDirection, paSlaveIndex),
          mType(paType) {
        }
    };

    void setConfig(Config *paConfig) override;

    void addSlaveHandle(size_t paIndex, std::unique_ptr<IOHandle> paHandle) override;

    void dropSlaveHandles(size_t paIndex) override;

  protected:
    const char *init();

    IOHandle *createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) override;

    void deInit() override;

    void runLoop() override;

    HMIConfig mConfig;

  private:
    bool isSlaveAvailable(size_t paIndex);

    bool checkSlaveType(size_t paIndex, int paType);
};

#endif /* SRC_MODULES_HMI_MODULAR_HMIDEVICECONTROLLER_H_ */
