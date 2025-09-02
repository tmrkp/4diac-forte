#include "startup.h"

#include "HMIDriver.h"

void hmiStartupHook(int argc, char *arg[]) {
  HMIDriver::init();
}

void hmiMainFunctionHook() {
  HMIDriver::main();
}
