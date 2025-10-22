#pragma once

#include "driver/LVGLBaseDriver.h"

extern LVGLBaseDriver *driver;

void lvglStartupHook(int argc, char *arg[]);
void lvglMainFunctionHook();
