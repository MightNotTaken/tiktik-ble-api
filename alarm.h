#ifndef ALARM_H__
#define ALARM_H__
#include "ble-custom.h"
#include <functional>

#define ALARM_SERVICE_UUID          BLEUUID((uint16_t)0xFF10)
#define ALARM_TIME_UUID             BLEUUID((uint16_t)0xFF11)
#define ALARM_STATUS_UUID           BLEUUID((uint16_t)0xFF12)
#define ALARM_SNOOZE_UUID           BLEUUID((uint16_t)0xFF13)
#define ALARM_TRIGGER_UUID          BLEUUID((uint16_t)0xFF14)

namespace Alarm {
  void begin();
  void setAlarmTime(uint8_t hour, uint8_t minute, uint8_t days);
  void setAlarmStatus(bool active);
  void setSnooze(uint16_t minutes);
  void triggerAlarm();
  void onAlarmChange(std::function<void(uint8_t hour, uint8_t minute, uint8_t days, bool active)> callback);
  void onSnoozeCommand(std::function<void(uint16_t minutes)> callback);
};
#endif