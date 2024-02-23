#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DataPackages.h"

#define INDICATOR_LED_PIN 1

RF24 radio(9, 10);  // CE, CSN
GameData gameData;

const byte address[6] = "00001";

void setup() {
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  digitalWrite(INDICATOR_LED_PIN, LOW);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  gameData.secondsToPlay = 600;
}

void loop() {
  delay(1000);

  if (radio.write(&gameData, sizeof(gameData))) {
    digitalWrite(INDICATOR_LED_PIN, HIGH);
  } else {
    digitalWrite(INDICATOR_LED_PIN, LOW);
  }
  gameData.secondsToPlay -= 1;
}
