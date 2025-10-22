#pragma once

#include <functional>
#include <queue>
#include "criticalregion.h"

class LVGLBaseDriver {
  public:
    virtual ~LVGLBaseDriver() = default;

    virtual void init();
    virtual void runLoop();

    void runLater(std::function<void()> task);

    static CSyncObject timerMutex;

  protected:
    CSyncObject taskQueueMutex;
    std::queue<std::function<void()>> taskQueue;
};
