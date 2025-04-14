#ifndef WOMEN_HEALTH_H__
#define WOMEN_HEALTH_H__
#include "ble-custom.h"
#include <functional>

// Standard UUIDs where available, custom for specific features
#define WOMEN_HEALTH_SERVICE_UUID        BLEUUID((uint16_t)0x1820)  // User Data Service
#define CYCLE_PHASE_UUID                 BLEUUID((uint16_t)0x2ADA)  // Custom
#define SYMPTOM_TRACKER_UUID             BLEUUID((uint16_t)0x2ADB)  // Custom
#define FERTILITY_STATUS_UUID            BLEUUID((uint16_t)0x2ADC)  // Custom

namespace WomenHealth {
  void begin();
  void setCyclePhase(uint8_t phase);
  void setSymptoms(uint16_t symptoms);
  void setFertilityStatus(uint8_t status);
  void onCycleUpdate(std::function<void(uint8_t phase, uint16_t symptoms)> callback);
};
#endif