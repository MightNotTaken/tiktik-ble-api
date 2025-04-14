#ifndef BATTERY_H__
#define BATTERY_H__

#include "ble-custom.h"

#define BATTERY_SERVICE_UUID        BLEUUID((uint16_t)0x180F)
#define BATTERY_LEVEL_UUID          BLEUUID((uint16_t)0x2A19)

namespace Battery {
  void begin();
  void setLevel(uint8_t level);
}

#endif
