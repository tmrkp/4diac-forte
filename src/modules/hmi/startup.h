#pragma once

#include <functional>

void runLater(std::function<void()> task);

void hmiStartupHook(int argc, char *arg[]);
void hmiMainFunctionHook();
