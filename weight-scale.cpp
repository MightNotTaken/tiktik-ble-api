#include "weight-scale.h"
#include <ctime>

namespace WeightScale {
  BLEService* service;
  BLECharacteristic* measurementCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(WEIGHT_SCALE_SERVICE_UUID);

    measurementCharacteristic = service->createCharacteristic(
        WEIGHT_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    measurementCharacteristic->addDescriptor(new BLE2902());

    service->start();
  }

  void setValue(float weight, bool timestamp) {
    uint8_t data[7];
    data[0] = timestamp ? 0x02 : 0x00; // Flags
    memcpy(&data[1], &weight, 4);
    
    if(timestamp) {
      uint16_t currentTime = static_cast<uint16_t>(time(nullptr));
      memcpy(&data[5], &currentTime, 2);
    }
    
    measurementCharacteristic->setValue(data, timestamp ? 7 : 5);
    measurementCharacteristic->notify();
  }
}