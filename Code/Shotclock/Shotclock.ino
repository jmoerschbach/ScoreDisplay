#include <nRF24L01.h>
#include <RF24.h>
#include "SevenSegmentVisualization.h"
#include "DataPackages.h"

RF24 radio(9, 10);  // CE, CSN
SevenSegmentVisualization visualization;

// this must be either SHOT0 or SHOT1
const byte address[6] = ADDRESS_SHOTCLOCK_0;
// const byte address[6] = ADDRESS_SHOTCLOCK_1;

ShotclockData data;

void setup() {
  radio.begin();
  radio.setChannel(CHANNEL_SYSTEM_0);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
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
