#include "LVGLDriverInterface.h"

CSyncObject LVGLDriverInterface::timerMutex;

void LVGLDriverInterface::runLater(std::function<void()> task) {
  CCriticalRegion criticalRegion(taskQueueMutex);
  taskQueue.push(std::move(task));
}