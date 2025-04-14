#include "battery.h"

namespace Battery {
  BLEService* service;
  BLECharacteristic* batteryLevelCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(BATTERY_SERVICE_UUID);

    batteryLevelCharacteristic = service->createCharacteristic(
      BATTERY_LEVEL_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );

    batteryLevelCharacteristic->addDescriptor(new BLE2902());
    batteryLevelCharacteristic->setValue((uint8_t*)"\x64", 1); // Default: 100%

    service->start();

    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(BATTERY_SERVICE_UUID);
  }

  void setLevel(uint8_t level) {
    batteryLevelCharacteristic->setValue(&level, 1);
    batteryLevelCharacteristic->notify();
  }
}
