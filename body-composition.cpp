#include "body-composition.h"
#include <string.h>

namespace BodyComposition {
  BLEService* service;
  BLECharacteristic* measurementCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(BODY_COMPOSITION_SERVICE_UUID);

    measurementCharacteristic = service->createCharacteristic(
        BODY_COMP_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    measurementCharacteristic->addDescriptor(new BLE2902());

    service->start();
  }

  void setValue(float weight, float fatPercentage, float muscleMass) {
    uint8_t data[13];
    data[0] = 0x03; // Units: kg, percentage, kg
    memcpy(&data[1], &weight, 4);
    memcpy(&data[5], &fatPercentage, 4);
    memcpy(&data[9], &muscleMass, 4);
    measurementCharacteristic->setValue(data, sizeof(data));
    measurementCharacteristic->notify();
  }
}