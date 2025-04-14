#include "device-info.h"

namespace DeviceInfo {
  BLEService* service;
  BLECharacteristic* manufacturerCharacteristic;
  BLECharacteristic* modelCharacteristic;
  BLECharacteristic* firmwareCharacteristic;
  BLECharacteristic* hardwareCharacteristic;

  void begin() {
    auto server = BLECustom::getServer();
    service = server->createService(DEVICE_INFO_SERVICE_UUID);

    manufacturerCharacteristic = service->createCharacteristic(
        MANUFACTURER_NAME_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    
    modelCharacteristic = service->createCharacteristic(
        MODEL_NUMBER_UUID,
        BLECharacteristic::PROPERTY_READ
    );

    firmwareCharacteristic = service->createCharacteristic(
        FIRMWARE_REVISION_UUID,
        BLECharacteristic::PROPERTY_READ
    );

    hardwareCharacteristic = service->createCharacteristic(
        HARDWARE_REVISION_UUID,
        BLECharacteristic::PROPERTY_READ
    );

    // Set default values
    setManufacturer("tiktik Global");
    setModelNumber("TT-2025");
    setFirmwareRevision("1.0.0");
    setHardwareRevision("RevB");

    service->start();
  }

  void setManufacturer(const char* name) {
    manufacturerCharacteristic->setValue(name);
  }

  void setModelNumber(const char* number) {
    modelCharacteristic->setValue(number);
  }

  void setFirmwareRevision(const char* rev) {
    firmwareCharacteristic->setValue(rev);
  }

  void setHardwareRevision(const char* rev) {
    hardwareCharacteristic->setValue(rev);
  }
}