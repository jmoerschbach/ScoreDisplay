#ifndef _BATTERYMONITOR_h
#define _BATTERYMONITOR_h
#include <stdint.h>

class BatteryMonitor {
  public:
  void begin();
  uint8_t getSoCInPercent();
  private:
};
#endif