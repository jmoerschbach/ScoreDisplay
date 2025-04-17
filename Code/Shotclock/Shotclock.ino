#include <Arduino.h>
#include <RF24.h>
#include "Constants.h"
#include "SevenSegmentVisualization.h"
#include "DataPackages.h"
#if defined(BATTERY_POWERED)
#include "BatteryMonitor.h"
// minimal state of charge before display is disabled
constexpr int SOC_THRESHOLD = 5;
BatteryMonitor monitor;
#endif
constexpr int BUZZER_PIN = A1;

RF24 radio(9, 10);  // CE, CSN
SevenSegmentVisualization visualization;

ShotclockData data;

void setup() {
  radio.begin();
  visualization.begin();
  radio.setChannel(CHANNEL);
  // radio.openReadingPipe(0, ADDRESS_SHOTCLOCK_0);
  radio.openReadingPipe(0, ADDRESS_SHOTCLOCK_1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);


#if defined(BATTERY_POWERED)
  monitor.begin();
  data.secondsToShot = min(99, monitor.getSoCInPercent());
#endif
  visualization.visualize(data);
  delay(1000);
}

void loop() {
#if defined(BATTERY_POWERED)
  if (monitor.getSoCInPercent() < SOC_THRESHOLD) {
    data.enabled = false;
    visualization.visualize(data);
  } else
#endif
    if (radio.available()) {
    radio.read(&data, sizeof(data));
    visualization.visualize(data);
    digitalWrite(BUZZER_PIN, data.beep);
  }
}
