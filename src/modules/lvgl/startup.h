#pragma once

#include "driver/LVGLDriverInterface.h"

extern LVGLDriverInterface *driver;

void lvglStartupHook(int argc, char *arg[]);
void lvglMainFunctionHook();
