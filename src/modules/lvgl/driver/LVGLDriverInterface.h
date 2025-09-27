#pragma once

#include <functional>
#include <queue>
#include "criticalregion.h"

class LVGLDriverInterface {
  public:
    virtual ~LVGLDriverInterface() = default;

    virtual void init() = 0;
    virtual void runLoop() = 0;

    void runLater(std::function<void()> task);

    static CSyncObject timerMutex;

  protected:
    CSyncObject taskQueueMutex;
    std::queue<std::function<void()>> taskQueue;
};
