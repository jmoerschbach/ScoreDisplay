#include "BatteryMonitor.h"

constexpr int COMPARE_MATCH_1s = 62500;     // 1 * CLK_FREQ / PRESCALER

volatile bool tick_1s = false;

ISR(TIMER1_COMPB_vect) {
  OCR1B += COMPARE_MATCH_1s;
  tick_1s = true;
}

void configureTimer() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= B00000100;          // Prescaler = 256
  OCR1B = COMPARE_MATCH_1s;     // Timer Compare1B Register
  TIMSK1 |= B00000100;          // Enable Timer COMPB Interrupt
  sei();
}

void BatteryMonitor::begin() {

  calculateSoC();
  configureTimer();
}

void BatteryMonitor::loop() {
  if (tick_1s) {
    tick_1s = false;
    seconds_counter++;
  }
  if(seconds_counter > 1 * 60) {
    seconds_counter = 0;
    calculateSoC();
  }
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
