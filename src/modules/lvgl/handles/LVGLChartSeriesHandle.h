#pragma once

#include "io/mapper/io_handle.h"
#include "lvgl/lvgl.h"

using namespace forte::core::io;

class LVGLChartSeriesHandle : public IOHandle {
  public:
    LVGLChartSeriesHandle(IODeviceController *paController,
                         IOMapper::Direction paDirection,
                         CIEC_ANY::EDataTypeID paType,
                         lv_obj_t *paWidget);

    ~LVGLChartSeriesHandle() override = default;

    void set(const CIEC_ANY &) override;

    void get(CIEC_ANY &) override;

  private:
    lv_obj_t *mWidget;
    lv_chart_series_t *mSeries;
};
