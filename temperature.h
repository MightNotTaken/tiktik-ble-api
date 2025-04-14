#ifndef TEMPERATURE_H__
#define TEMPERATURE_H__
#include "ble-custom.h"

#define TEMPERATURE_SERVICE_UUID       BLEUUID((uint16_t)0x1809)
#define TEMPERATURE_MEASUREMENT_UUID   BLEUUID((uint16_t)0x2A1C)

namespace Temperature {
  void begin();
  void setValue(float celsius);
};
#endif