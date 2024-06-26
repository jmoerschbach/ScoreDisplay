#include <RF24.h>
#include "Constants.h"
#include "SevenSegmentVisualization.h"
#include "DataPackages.h"

RF24 radio(9, 10);  // CE, CSN
SevenSegmentVisualization visualization;


MainDisplayData data;
void setup() {
  radio.begin();
  radio.setChannel(CHANNEL);
  radio.openReadingPipe(0, ADDRESS_MAIN_DISPLAY);
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
