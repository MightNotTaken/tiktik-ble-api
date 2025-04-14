#include "women-health.h"

namespace WomenHealth {
  BLEService* service;
  BLECharacteristic* cyclePhaseCharacteristic;
  BLECharacteristic* symptomCharacteristic;
  BLECharacteristic* fertilityCharacteristic;
  
  std::function<void(uint8_t, uint16_t)> cycleCallback = nullptr;

  class CycleCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) override {
      if (cycleCallback) {
        uint8_t* data = characteristic->getData();
        if (data && characteristic->getLength() >= 3) {
          cycleCallback(data[0], (data[1] << 8) | data[2]);
        }
      }
    }
  };

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(WOMEN_HEALTH_SERVICE_UUID);

    // Cycle Phase Characteristic (Read/Notify/Write)
    cyclePhaseCharacteristic = service->createCharacteristic(
        CYCLE_PHASE_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY |
        BLECharacteristic::PROPERTY_WRITE
    );
    cyclePhaseCharacteristic->addDescriptor(new BLE2902());
    cyclePhaseCharacteristic->setCallbacks(new CycleCallback());
    cyclePhaseCharacteristic->setValue((uint8_t*)"\x00", 1);  // Default: Menstrual

    // Symptom Tracker Characteristic (Read/Notify)
    symptomCharacteristic = service->createCharacteristic(
        SYMPTOM_TRACKER_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    symptomCharacteristic->addDescriptor(new BLE2902());
    symptomCharacteristic->setValue((uint8_t*)"\x00\x00", 2);  // Default: No symptoms

    // Fertility Status Characteristic (Read/Notify)
    fertilityCharacteristic = service->createCharacteristic(
        FERTILITY_STATUS_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    fertilityCharacteristic->addDescriptor(new BLE2902());
    fertilityCharacteristic->setValue((uint8_t*)"\x00", 1);  // Default: Low

    service->start();
    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(WOMEN_HEALTH_SERVICE_UUID);
  }

  void setCyclePhase(uint8_t phase) {
    cyclePhaseCharacteristic->setValue(&phase, 1);
    cyclePhaseCharacteristic->notify();
  }

  void setSymptoms(uint16_t symptoms) {
    uint8_t data[2] = {(uint8_t)(symptoms >> 8), (uint8_t)symptoms};
    symptomCharacteristic->setValue(data, 2);
    symptomCharacteristic->notify();
  }

  void setFertilityStatus(uint8_t status) {
    fertilityCharacteristic->setValue(&status, 1);
    fertilityCharacteristic->notify();
  }

  void onCycleUpdate(std::function<void(uint8_t, uint16_t)> callback) {
    cycleCallback = callback;
  }
}