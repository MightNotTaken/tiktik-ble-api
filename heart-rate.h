#ifndef HEART_RATE_H__
#define HEART_RATE_H__
#include "ble-custom.h"
#include <functional>

#define HEART_RATE_SERVICE_UUID                  BLEUUID((uint16_t)0x180D)
#define HEART_RATE_MEASUREMENT_UUID              BLEUUID((uint16_t)0x2A37)
#define HEART_RATE_SENSOR_LOCATION_UUID          BLEUUID((uint16_t)0x2A38)
#define HEART_RATE_CONTROL_POINT_UUID            BLEUUID((uint16_t)0x2A39)

namespace HeartRate {
  void begin();
  void setValue(uint8_t hr);
  void setSensorLocation(uint8_t location);
  void onControlCommand(std::function<void(uint8_t)> callback);
};

 
#endif