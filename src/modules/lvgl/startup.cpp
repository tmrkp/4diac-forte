#include "startup.h"

#include "LVGLDriver.h"

void lvglStartupHook(int argc, char *arg[]) {
  LVGLDriver::init();
}

void lvglMainFunctionHook() {
  LVGLDriver::main();
}
