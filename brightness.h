#ifndef BRIGHTNESS_H__
#define BRIGHTNESS_H__
#include "ble-custom.h"

#define BRIGHTNESS_SERVICE_UUID      BLEUUID((uint16_t)0xFF01)
#define BRIGHTNESS_LEVEL_UUID        BLEUUID((uint16_t)0xFF02)

namespace Brightness {
  void begin();
  void setLevel(uint8_t level);
  void onLevelChanged(std::function<void(uint8_t)> callback);
}
#endif