#ifndef _BATTERYMONITOR_h
#define _BATTERYMONITOR_h
#include <stdint.h>
#include <Arduino.h>  // analogRead


constexpr int BATTERY_PIN = A6;

class BatteryMonitor {
public:
  void begin();
  void loop();
  uint8_t getSoCInPercent();
private:
  void calculateSoC();
  int measure(uint8_t numberOfMeasuers);
  uint8_t soc = 100;
  uint16_t seconds_counter = 0;
};
#endif