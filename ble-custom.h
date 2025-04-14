#ifndef BLE_CUSTOM_H__
#define BLE_CUSTOM_H__

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>

namespace BLECustom {
  void begin(String name);
  BLEServer* getServer();
  void startAdvertising();
}

#endif