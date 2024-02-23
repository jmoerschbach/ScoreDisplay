#include <nRF24L01.h>
#include <RF24.h>
#include "Visualization.h"
#include "SerialConsoleVisualization.h"
#include "SevenSegmentVisualization.h"

RF24 radio(9, 10);  // CE, CSN
SerialConsoleVisualization visualization;
SevenSegmentVisualization visualization2;


const byte address[6] = "00001";


GameData data;
void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();


  visualization2.begin();

  data.secondsToPlay = 600;
  data.awayScore = 3;
  data.homeScore = 1;
  data.halftime = 1;
  visualization2.visualize(data);
}


void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    visualization2.visualize(data);
  }
}
