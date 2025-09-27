#include "LVGLChartSeriesHandle.h"

#include "LVGLDeviceController.h"
#include "forte_dword.h"

LVGLChartSeriesHandle::LVGLChartSeriesHandle(IODeviceController *paController,
                                             IOMapper::Direction paDirection,
                                             CIEC_ANY::EDataTypeID paType,
                                             lv_obj_t *paWidget) :
    IOHandle(paController, paDirection, paType),
    mWidget(paWidget) {
  mSeries = lv_chart_add_series(mWidget, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
}

void LVGLChartSeriesHandle::set(const CIEC_ANY &paState) {
  auto *controller = static_cast<LVGLDeviceController *>(mController);
  if (mType == CIEC_ANY::e_DWORD) {
    TForteDWord dword = static_cast<const CIEC_DWORD &>(paState);
    controller->runLater(
        [this, value = static_cast<int32_t>(dword)] { lv_chart_set_next_value(mWidget, mSeries, value); });
  }
}

void LVGLChartSeriesHandle::get(CIEC_ANY &paState) {
}
