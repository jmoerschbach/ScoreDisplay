#include <nRF24L01.h>
#include <RF24.h>
#include "SevenSegmentVisualization.h"
#include "DataPackages.h"

RF24 radio(9, 10);  // CE, CSN
SevenSegmentVisualization visualization;

ShotclockData data;

void setup() {
  radio.begin();
  radio.setChannel(CHANNEL_SYSTEM_0);
  // radio.setChannel(CHANNEL_SYSTEM_1);
  // radio.openReadingPipe(0, ADDRESS_SHOTCLOCK_0);
  radio.openReadingPipe(0, ADDRESS_SHOTCLOCK_1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();


  visualization.begin();
  visualization.visualize(data);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    visualization.visualize(data);
  }
}
