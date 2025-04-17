#include "BatteryMonitor.h"

void BatteryMonitor::begin() {

  calculateSoC();
  //start timer to calculate SoC every x min
}

uint8_t BatteryMonitor::getSoCInPercent() {
  return soc;
}
void BatteryMonitor::calculateSoC() {
  int averagedValue = measure(10);
  soc = map(averagedValue, 700, 850, 0, 100);
}
int BatteryMonitor::measure(uint8_t numberOfMeasuers) {

  int rawValue = 0;
  for (uint8_t i = 0; i < numberOfMeasuers; i++) {
    rawValue += analogRead(BATTERY_PIN);
  }

  return rawValue / numberOfMeasuers;
}
