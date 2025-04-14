#include "brightness.h"

namespace Brightness {
  BLEService* service;
  BLECharacteristic* levelCharacteristic;
  std::function<void(uint8_t)> levelCallback = nullptr;

  class LevelCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) override {
      if (levelCallback) {
        uint8_t* data = characteristic->getData();
        if (data) levelCallback(data[0]);
      }
    }
  };

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(BRIGHTNESS_SERVICE_UUID);

    levelCharacteristic = service->createCharacteristic(
      BRIGHTNESS_LEVEL_UUID,
      BLECharacteristic::PROPERTY_READ | 
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
    );
    
    levelCharacteristic->addDescriptor(new BLE2902());
    levelCharacteristic->setCallbacks(new LevelCallback());
    levelCharacteristic->setValue((uint8_t*)"\x64", 1); // Default: 100%

    service->start();
    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(BRIGHTNESS_SERVICE_UUID);
  }

  void setLevel(uint8_t level) {
    levelCharacteristic->setValue(&level, 1);
    levelCharacteristic->notify();
  }

  void onLevelChanged(std::function<void(uint8_t)> callback) {
    levelCallback = callback;
  }
}