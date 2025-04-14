#ifndef BODY_COMPOSITION_H__
#define BODY_COMPOSITION_H__
#include "ble-custom.h"

#define BODY_COMPOSITION_SERVICE_UUID  BLEUUID((uint16_t)0x181B)
#define BODY_COMP_MEASUREMENT_UUID     BLEUUID((uint16_t)0x2A9B)

namespace BodyComposition {
  void begin();
  void setValue(float weight, float fatPercentage, float muscleMass);
};
#endif