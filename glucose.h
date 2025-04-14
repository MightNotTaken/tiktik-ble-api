#ifndef GLUCOSE_H__
#define GLUCOSE_H__
#include "ble-custom.h"

#define GLUCOSE_SERVICE_UUID           BLEUUID((uint16_t)0x1808)
#define GLUCOSE_MEASUREMENT_UUID       BLEUUID((uint16_t)0x2A18)

namespace Glucose {
  void begin();
  void setValue(float mmolL, uint16_t sequenceNumber);
};
#endif