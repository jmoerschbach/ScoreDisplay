#include <Arduino.h>
#include <RF24.h>
#include "DataPackages.h"
#include "Game.h"

#define INDICATOR_LED_PIN 1


RF24 radio(9, 10);  // CE, CSN

MainDisplayData mainDisplayData;
Game game;

void onDataChangedCallback() {
  mainDisplayData.homeScore = game.getHomeScore();
  mainDisplayData.awayScore = game.getAwayScore();
  mainDisplayData.secondsToPlay = game.getTimeLeftToPlay();
  send();
}

const byte address[6] = "00001";

void send() {
  if (radio.write(&mainDisplayData, sizeof(mainDisplayData))) {
    digitalWrite(INDICATOR_LED_PIN, HIGH);
  } else {
    digitalWrite(INDICATOR_LED_PIN, LOW);
  }
}

void setup() {
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  digitalWrite(INDICATOR_LED_PIN, LOW);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  game.begin(onDataChangedCallback);

  //   mainDisplayData.awayScoreColor = CRGB::Yellow;
  //   mainDisplayData.homeScoreColor = CRGB::Red;
  //   mainDisplayData.timeColor = CRGB::Green;
  //   mainDisplayData.halftimeColor = CRGB::Blue;
  // mainDisplayData.brightness = 255;
}

void loop() {
  game.loop();
}
