#include "startup.h"

#include "driver/SDL2Driver.h"

SDL2Driver sdl2driver;
LVGLBaseDriver *driver = &sdl2driver;

void lvglStartupHook(int argc, char *arg[]) {
  sdl2driver.init();
}

void lvglMainFunctionHook() {
  sdl2driver.runLoop();
}
