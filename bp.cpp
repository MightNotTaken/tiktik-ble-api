#include "bp.h"

namespace BloodPressure {
  BLEService* service;
  BLECharacteristic* measurementCharacteristic;
  BLECharacteristic* featureCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(BLOOD_PRESSURE_SERVICE_UUID);

    // Measurement Characteristic (Notify)
    measurementCharacteristic = service->createCharacteristic(
        BLOOD_PRESSURE_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    measurementCharacteristic->addDescriptor(new BLE2902());

    // Feature Characteristic (Read)
    featureCharacteristic = service->createCharacteristic(
        BLOOD_PRESSURE_FEATURE_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    setFeatures(0x0001); // Default feature: Body Movement Detection support

    service->start();
    
    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(BLOOD_PRESSURE_SERVICE_UUID);
  }

  void setValue(uint16_t systolic, uint16_t diastolic, uint16_t map) {
    uint8_t data[7];
    data[0] = 0x00; // Flags (0mmHg, no timestamp/pulse rate)
    memcpy(&data[1], &systolic, 2);
    memcpy(&data[3], &diastolic, 2);
    memcpy(&data[5], &map, 2);
    measurementCharacteristic->setValue(data, sizeof(data));
    measurementCharacteristic->notify();
  }

  void setFeatures(uint16_t features) {
    featureCharacteristic->setValue(features);
  }
}