#include "spo2.h"
#include <string.h>

namespace SpO2 {
  BLEService* service;
  BLECharacteristic* measurementCharacteristic;
  BLECharacteristic* featureCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(SPO2_SERVICE_UUID);

    // Measurement Characteristic (Notify)
    measurementCharacteristic = service->createCharacteristic(
        SPO2_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    measurementCharacteristic->addDescriptor(new BLE2902());

    // Feature Characteristic (Read)
    featureCharacteristic = service->createCharacteristic(
        SPO2_FEATURE_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    setFeatures(0x0001); // Default: Spot-check measurement supported

    service->start();
    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(SPO2_SERVICE_UUID);
  }

  void setValue(uint8_t spo2, uint16_t pulseRate) {
    uint8_t flags = 0x01; // Pulse Rate present in measurement
    uint8_t data[5];
    
    data[0] = flags;
    data[1] = spo2;
    memcpy(&data[2], &pulseRate, 2);
    
    // Add timestamp if needed (commented out)
    // uint16_t timestamp = 0;
    // memcpy(&data[4], &timestamp, 2);
    
    measurementCharacteristic->setValue(data, pulseRate ? 4 : 2);
    measurementCharacteristic->notify();
  }

  void setFeatures(uint16_t features) {
    featureCharacteristic->setValue(features);
  }
}