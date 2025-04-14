#ifndef DEVICE_INFO_H__
#define DEVICE_INFO_H__
#include "ble-custom.h"

#define DEVICE_INFO_SERVICE_UUID       BLEUUID((uint16_t)0x180A)
#define MANUFACTURER_NAME_UUID         BLEUUID((uint16_t)0x2A29)
#define MODEL_NUMBER_UUID              BLEUUID((uint16_t)0x2A24)
#define FIRMWARE_REVISION_UUID         BLEUUID((uint16_t)0x2A26)
#define HARDWARE_REVISION_UUID         BLEUUID((uint16_t)0x2A27)

namespace DeviceInfo {
  void begin();
  void setManufacturer(const char* name);
  void setModelNumber(const char* number);
  void setFirmwareRevision(const char* rev);
  void setHardwareRevision(const char* rev);
};
#endif