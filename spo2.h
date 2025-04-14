#ifndef SPO2_H__
#define SPO2_H__
#include "ble-custom.h"
#include <functional>

#define SPO2_SERVICE_UUID             BLEUUID((uint16_t)0x1822)
#define SPO2_MEASUREMENT_UUID         BLEUUID((uint16_t)0x2A5F)
#define SPO2_FEATURE_UUID             BLEUUID((uint16_t)0x2A53)

namespace SpO2 {
  void begin();
  void setValue(uint8_t spo2, uint16_t pulseRate = 0);
  void setFeatures(uint16_t features);
};
#endif