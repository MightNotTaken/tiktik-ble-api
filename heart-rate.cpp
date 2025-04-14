#include "heart-rate.h"

namespace HeartRate {
  BLEService* service;
  BLECharacteristic* measurementCharacteristic;
  BLECharacteristic* sensorLocationCharacteristic;
  BLECharacteristic* controlPointCharacteristic;

  std::function<void(uint8_t)> controlPointCallback = nullptr; 
  
  class ControlPointCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) override {
      if (controlPointCallback) {
        uint8_t* data = characteristic->getData();
        if (data) controlPointCallback(data[0]);
      }
    }
  };

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(HEART_RATE_SERVICE_UUID);

    
    measurementCharacteristic = service->createCharacteristic(
        HEART_RATE_MEASUREMENT_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    measurementCharacteristic->addDescriptor(new BLE2902());

    
    sensorLocationCharacteristic = service->createCharacteristic(
        HEART_RATE_SENSOR_LOCATION_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    sensorLocationCharacteristic->setValue((uint8_t*)"\x02", 1); 

    
    controlPointCharacteristic = service->createCharacteristic(
        HEART_RATE_CONTROL_POINT_UUID,
        BLECharacteristic::PROPERTY_WRITE
    );
    controlPointCharacteristic->setCallbacks(new ControlPointCallback());

    
    service->start();
    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(HEART_RATE_SERVICE_UUID);
  }

  
  void setValue(uint8_t hr) {
    uint8_t data[2];
    data[0] = 0x00;  
    data[1] = hr;
    measurementCharacteristic->setValue(data, 2);
    measurementCharacteristic->notify();
  }

  
  void setSensorLocation(uint8_t location) {
    sensorLocationCharacteristic->setValue(&location, 1);
  }

  
  void onControlCommand(std::function<void(uint8_t)> callback) {
    controlPointCallback = callback;
  }
}
