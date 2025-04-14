#ifndef BLOOD_PRESSURE_H__
#define BLOOD_PRESSURE_H__

#include "ble-custom.h"

#define BLOOD_PRESSURE_SERVICE_UUID          BLEUUID((uint16_t)0x1810)
#define BLOOD_PRESSURE_MEASUREMENT_UUID      BLEUUID((uint16_t)0x2A35)
#define BLOOD_PRESSURE_FEATURE_UUID          BLEUUID((uint16_t)0x2A49)

namespace BloodPressure {
  void begin();
  void setValue(uint16_t systolic, uint16_t diastolic, uint16_t map);
  void setFeatures(uint16_t features);
}
#endif