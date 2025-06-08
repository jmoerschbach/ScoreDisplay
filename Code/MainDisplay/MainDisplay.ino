#include <RF24.h>
#include "Constants.h"
#include "SevenSegmentVisualization.h"
#include "DataPackages.h"

constexpr int HORN_PIN = 0;

RF24 radio(9, 10);  // CE, CSN
SevenSegmentVisualization visualization;


MainDisplayData data;
void setup() {
  pinMode(HORN_PIN, OUTPUT);
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

    if (data.beep) {
      digitalWrite(HORN_PIN, HIGH);
    } else {
      digitalWrite(HORN_PIN, LOW);
    }
  }
}
