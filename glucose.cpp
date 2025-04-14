#include "glucose.h"
#include <ctime>

namespace Glucose {
  BLEService* service;
  BLECharacteristic* measurementCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(GLUCOSE_SERVICE_UUID);

    measurementCharacteristic = service->createCharacteristic(
        GLUCOSE_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    measurementCharacteristic->addDescriptor(new BLE2902());

    service->start();
  }

  void setValue(float mmolL, uint16_t sequenceNumber) {
    uint8_t data[10];
    data[0] = 0x01; // Context: concentration only
    memcpy(&data[1], &sequenceNumber, 2);
    
    // Convert to IEEE-11073 32-bit float
    int32_t encoded = (int32_t)(mmolL * 100000);
    memcpy(&data[3], &encoded, 4);
    
    // Add timestamp
    uint16_t currentTime = static_cast<uint16_t>(time(nullptr));
    memcpy(&data[7], &currentTime, 2);
    
    measurementCharacteristic->setValue(data, sizeof(data));
    measurementCharacteristic->notify();
  }
}