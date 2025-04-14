#include "alarm.h"
#include <string.h>

namespace Alarm {
  BLEService* service;
  BLECharacteristic* timeCharacteristic;
  BLECharacteristic* statusCharacteristic;
  BLECharacteristic* snoozeCharacteristic;
  BLECharacteristic* triggerCharacteristic;
  
  std::function<void(uint8_t, uint8_t, uint8_t, bool)> alarmCallback = nullptr;
  std::function<void(uint16_t)> snoozeCallback = nullptr;

  class TimeCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) override {
      if (alarmCallback) {
        uint8_t* data = characteristic->getData();
        if (data && characteristic->getLength() >= 3) {
          alarmCallback(data[0], data[1], data[2], statusCharacteristic->getValue()[0]);
        }
      }
    }
  };

  class StatusCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) override {
      if (alarmCallback) {
        uint8_t* data = characteristic->getData();
        uint8_t* timeData = timeCharacteristic->getData();
        if (data && timeData) {
          alarmCallback(timeData[0], timeData[1], timeData[2], data[0]);
        }
      }
    }
  };

  class SnoozeCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) override {
      if (snoozeCallback) {
        uint8_t* data = characteristic->getData();
        if (data && characteristic->getLength() >= 2) {
          uint16_t minutes = (data[0] << 8) | data[1];
          snoozeCallback(minutes);
        }
      }
    }
  };

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(ALARM_SERVICE_UUID);

    // Time Characteristic (HH:MM, Days bitmask)
    timeCharacteristic = service->createCharacteristic(
        ALARM_TIME_UUID,
        BLECharacteristic::PROPERTY_READ | 
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    timeCharacteristic->setCallbacks(new TimeCallback());
    timeCharacteristic->setValue((uint8_t*)"\x00\x00\x00", 3); // 00:00, no days

    // Status Characteristic
    statusCharacteristic = service->createCharacteristic(
        ALARM_STATUS_UUID,
        BLECharacteristic::PROPERTY_READ | 
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    statusCharacteristic->setCallbacks(new StatusCallback());
    statusCharacteristic->setValue((uint8_t*)"\x00", 1); // Off

    // Snooze Characteristic
    snoozeCharacteristic = service->createCharacteristic(
        ALARM_SNOOZE_UUID,
        BLECharacteristic::PROPERTY_READ | 
        BLECharacteristic::PROPERTY_WRITE
    );
    snoozeCharacteristic->setCallbacks(new SnoozeCallback());
    snoozeCharacteristic->setValue((uint8_t*)"\x00\x00", 2); // 0 minutes

    // Trigger Characteristic (Notify only)
    triggerCharacteristic = service->createCharacteristic(
        ALARM_TRIGGER_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    triggerCharacteristic->addDescriptor(new BLE2902());

    service->start();
    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->addServiceUUID(ALARM_SERVICE_UUID);
  }

  void setAlarmTime(uint8_t hour, uint8_t minute, uint8_t days) {
    uint8_t data[3] = {hour, minute, days};
    timeCharacteristic->setValue(data, 3);
    timeCharacteristic->notify();
  }

  void setAlarmStatus(bool active) {
    uint8_t value = active ? 0x01 : 0x00;
    statusCharacteristic->setValue(&value, 1);
    statusCharacteristic->notify();
  }

  void setSnooze(uint16_t minutes) {
    uint8_t data[2] = {(uint8_t)(minutes >> 8), (uint8_t)minutes};
    snoozeCharacteristic->setValue(data, 2);
  }

  void triggerAlarm() {
    uint8_t data = 0x01;
    triggerCharacteristic->setValue(&data, 1);
    triggerCharacteristic->notify();
  }

  void onAlarmChange(std::function<void(uint8_t, uint8_t, uint8_t, bool)> callback) {
    alarmCallback = callback;
  }

  void onSnoozeCommand(std::function<void(uint16_t)> callback) {
    snoozeCallback = callback;
  }
}