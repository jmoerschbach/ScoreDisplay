#include <Arduino.h>
#include <RF24.h>
#include "DataPackages.h"
#include "Game.h"
#include "Utils.h"

constexpr int INDICATOR_LED_PIN = 1;
constexpr byte mainDisplayAddress[6] = ADDRESS_MAINDISPLAY;
constexpr byte firstShotclockAddress[6] = ADDRESS_SHOTCLOCK_0;
constexpr byte secondShotclockAddress[6] = ADDRESS_SHOTCLOCK_1;

RF24 radio(9, 10);  // CE, CSN
MainDisplayData mainDisplayData;
ShotclockData shotclockData;
Game game;

void onDataChangedCallback() {
  mainDisplayData.homeScore = game.getHomeScore();
  mainDisplayData.awayScore = game.getAwayScore();
  mainDisplayData.secondsToPlay = game.getTimeLeftToPlay();
  send();
}


void send() {
  bool success = false;

  radio.openWritingPipe(mainDisplayAddress);
  success &= radio.write(&mainDisplayData, sizeof(mainDisplayData));

  radio.openWritingPipe(firstShotclockAddress);
  success &= radio.write(&shotclockData, sizeof(shotclockData));

  radio.openWritingPipe(secondShotclockAddress);
  success &= radio.write(&shotclockData, sizeof(shotclockData));

  if (success) {
    digitalWrite(INDICATOR_LED_PIN, HIGH);
  } else {
    digitalWrite(INDICATOR_LED_PIN, LOW);
  }

  // if (radio.write(&mainDisplayData, sizeof(mainDisplayData))) {
  //   digitalWrite(INDICATOR_LED_PIN, HIGH);
  // } else {
  //   digitalWrite(INDICATOR_LED_PIN, LOW);
  // }
}

void setup() {
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  digitalWrite(INDICATOR_LED_PIN, LOW);
  radio.begin();
  radio.setChannel(CHANNEL_SYSTEM_0);
  radio.openWritingPipe(mainDisplayAddress);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  game.begin(onDataChangedCallback);
}

void loop() {
  game.loop();
}
