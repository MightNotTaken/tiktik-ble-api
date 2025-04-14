#ifndef WEIGHT_SCALE_H__
#define WEIGHT_SCALE_H__
#include "ble-custom.h"

#define WEIGHT_SCALE_SERVICE_UUID      BLEUUID((uint16_t)0x181D)
#define WEIGHT_MEASUREMENT_UUID        BLEUUID((uint16_t)0x2A9D)

namespace WeightScale {
  void begin();
  void setValue(float weight, bool timestamp = false);
};
#endif