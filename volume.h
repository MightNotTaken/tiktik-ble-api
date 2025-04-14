#ifndef VOLUME_H__
#define VOLUME_H__
#include "ble-custom.h"

#define VOLUME_SERVICE_UUID          BLEUUID((uint16_t)0xFF03)
#define VOLUME_LEVEL_UUID            BLEUUID((uint16_t)0xFF04)

namespace Volume {
  void begin();
  void setLevel(uint8_t level);
  void onLevelChanged(std::function<void(uint8_t)> callback);
}
#endif