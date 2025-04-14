#include "temperature.h"

namespace Temperature {
  BLEService* service;
  BLECharacteristic* measurementCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(TEMPERATURE_SERVICE_UUID);

    measurementCharacteristic = service->createCharacteristic(
        TEMPERATURE_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    measurementCharacteristic->addDescriptor(new BLE2902());

    service->start();
  }

  void setValue(float celsius) {
    int16_t temp = celsius * 100; // Convert to IEEE-11073 format
    uint8_t data[5];
    data[0] = 0x00; // Flags
    memcpy(&data[1], &temp, 2);
    // Optional timestamp could be added here
    measurementCharacteristic->setValue(data, 3);
    measurementCharacteristic->notify();
  }
}