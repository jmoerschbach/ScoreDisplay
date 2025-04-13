#include <Arduino.h>
#include <RF24.h>
#include "Constants.h"
#include "SevenSegmentVisualization.h"
#include "BatteryMonitor.h"
#include "DataPackages.h"

constexpr int BUZZER_PIN = A1;

RF24 radio(9, 10);  // CE, CSN
SevenSegmentVisualization visualization;
BatteryMonitor monitor;

ShotclockData data;

void setup() {
  radio.begin();
  monitor.begin();
  radio.setChannel(CHANNEL);
  // radio.openReadingPipe(0, ADDRESS_SHOTCLOCK_0);
  radio.openReadingPipe(0, ADDRESS_SHOTCLOCK_1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);




  visualization.begin();
  visualization.visualize(data);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    visualization.visualize(data);
    digitalWrite(BUZZER_PIN, data.beep);
  }
}
