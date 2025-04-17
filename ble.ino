#include "ble-custom.h"
#include "heart-rate.h"
#include "battery.h"
#include "bp.h"
#include "brightness.h"
#include "volume.h"
#include "spo2.h"
#include "women-health.h"
#include "device-info.h"
#include "body-composition.h"
#include "weight-scale.h"
#include "glucose.h"
#include "temperature.h"
#include "alarm.h"


void setup() {
  Serial.begin(115200);
  BLECustom::begin("tiktik");
  HeartRate::begin();
  Battery::begin();
  BloodPressure::begin();
  Brightness::begin();
  Volume::begin();
  SpO2::begin();
  // WomenHealth::begin();
  // DeviceInfo::begin();
  // BodyComposition::begin();
  // WeightScale::begin();
  // Glucose::begin();
  // Temperature::begin();

  Battery::setLevel(87);
  HeartRate::onControlCommand([](uint8_t data) {
    Serial.printf("data: %d\n", data);
  });
  
  Brightness::onLevelChanged([](uint8_t level) {
    Serial.printf("Brightness changed: %d%%\n", level);
    // Add actual brightness control logic here
  });

  Volume::onLevelChanged([](uint8_t level) {
    Serial.printf("Volume changed: %d%%\n", level);
    // Add actual volume control logic here
  });

  // // Add callback for cycle updates
  // WomenHealth::onCycleUpdate([](uint8_t phase, uint16_t symptoms) {
  //   Serial.printf("Cycle Update - Phase: %d, Symptoms: 0x%04X\n", phase, symptoms);
  //   // Add actual logic here (e.g., update display, log data)
  // });

  //  Alarm::onAlarmChange([](uint8_t h, uint8_t m, uint8_t days, bool active) {
  //   Serial.printf("Alarm %s at %02d:%02d (Days: 0x%02X)\n", 
  //                active ? "set" : "unset", h, m, days);
  // });

  // Alarm::onSnoozeCommand([](uint16_t minutes) {
  //   Serial.printf("Snooze activated for %d minutes\n", minutes);
  // });

  BLECustom::startAdvertising();
}

void loop() {
  static uint16_t bp = 120;
  HeartRate::setValue(72 + random(5) - 5);
  BloodPressure::setValue(bp, 80, 90);
  if(bp++ > 130) bp = 120;
  
  static uint8_t spo2 = 97;
  static uint16_t pulse = 72;
  SpO2::setValue(spo2, pulse);
  spo2 = (spo2 + random(2)) % 100;
  pulse = 60 + random(20);
  
  static uint8_t ambientLight = 50;
  Brightness::setLevel(ambientLight++ % 100);
  static uint8_t cyclePhase = 0;
  static uint16_t symptoms = 0;
  
  // WomenHealth::setCyclePhase(cyclePhase);
  // WomenHealth::setSymptoms(symptoms);
  // WomenHealth::setFertilityStatus(random(3)); // 0-2
  
  // cyclePhase = (cyclePhase + 1) % 4; // 0-3 phases
  // symptoms = random(0xFFFF); // Simulate symptom changes
  
  // static float weight = 70.5f;
  // WeightScale::setValue(weight);
  // weight += 0.1f;
  
  // static float temp = 36.6f;
  // Temperature::setValue(temp);
  // temp += 0.1f;
  // static bool alarmTriggered = false;
  // if(!alarmTriggered) {
  //   Alarm::triggerAlarm();
  //   alarmTriggered = true;
  // }
  delay(1000);
}
