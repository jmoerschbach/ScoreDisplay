#include <nRF24L01.h>
#include <RF24.h>
#include "SevenSegmentVisualization.h"
#include "DataPackages.h"

// this is the frequenzy offset
// this must be the same for all 3 components of a system:
// MainDisplay, Shotclocks, Controller
// It must be different between 2 systems
constexpr int UNIQUE_CHANNEL_PER_SYSTEM = 5;
// constexpr int UNIQUE_CHANNEL_PER_SYSTEM = 50;

RF24 radio(9, 10);  // CE, CSN
SevenSegmentVisualization visualization;

// this must be either SHOT0 or SHOT1
const byte address[6] = ADDRESS_SHOTCLOCK_0;
// const byte address[6] = ADDRESS_SHOTCLOCK_1;

ShotclockData data;

void setup() {
  radio.begin();
  radio.setChannel(UNIQUE_CHANNEL_PER_SYSTEM);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  data.secondsToShot = 59;


  visualization.begin();
  visualization.visualize(data);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    visualization.visualize(data);
  }
}
