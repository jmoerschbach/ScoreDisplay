#include <Arduino.h>
#include <RF24.h>
#include "DataPackages.h"
#include "Game.h"
#include "Utils.h"

#define INDICATOR_LED_PIN 1
// this is the frequenzy offset
// this must be the same for all 3 components of a system:
// MainDisplay, Shotclocks, Controller
// It must be different between 2 systems
constexpr int UNIQUE_CHANNEL_PER_SYSTEM = 5;
// constexpr int UNIQUE_CHANNEL_PER_SYSTEM = 50;


RF24 radio(9, 10);  // CE, CSN

MainDisplayData mainDisplayData;
Game game;

void onDataChangedCallback() {
  mainDisplayData.homeScore = game.getHomeScore();
  mainDisplayData.awayScore = game.getAwayScore();
  mainDisplayData.secondsToPlay = game.getTimeLeftToPlay();
  send();
}

const byte mainDisplayAddress[6] = ADDRESS_MAINDISPLAY;
const byte firstShotclockAddress[6] = ADDRESS_SHOTCLOCK_0;
const byte secondShotclockAddress[6] = ADDRESS_SHOTCLOCK_1;

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
  radio.setChannel(UNIQUE_CHANNEL_PER_SYSTEM);
  radio.openWritingPipe(mainDisplayAddress);
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
