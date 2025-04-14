#include "ble-custom.h"

namespace BLECustom {
  BLEServer* pServer = nullptr;
  void begin(String name) {
    BLEDevice::init(name.c_str());
    pServer = BLEDevice::createServer();
  }

  BLEServer* getServer() {
    return pServer;
  }

  void startAdvertising() {
    BLEAdvertising* adv = BLEDevice::getAdvertising();
    adv->start();
  }

}
