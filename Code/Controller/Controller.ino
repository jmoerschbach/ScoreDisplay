#include <Arduino.h>
#include <RF24.h>
#include "DataPackages.h"
#include "Game.h"
#include "Utils.h"

constexpr int INDICATOR_LED_PIN = 1;

RF24 radio(9, 10);  // CE, CSN
MainDisplayData mainDisplayData;
ShotclockData shotclockData;
Game game;

void onDataChangedCallback() {
  mainDisplayData.homeScore = game.getHomeScore();
  mainDisplayData.awayScore = game.getAwayScore();
  mainDisplayData.secondsToPlay = game.getTimeLeftToPlay();
  mainDisplayData.halftime = game.getHalfTime();

  shotclockData.secondsToShot = game.getTimeLeftToShoot();
  // shotclockData.enabled = game.getTimeLeftToShoot() != 55;

  send();
}


void send() {
  bool success = true;

  radio.openWritingPipe(ADDRESS_MAIN_DISPLAY);
  success &= radio.write(&mainDisplayData, sizeof(mainDisplayData));

  radio.openWritingPipe(ADDRESS_SHOTCLOCK_0);
  success &= radio.write(&shotclockData, sizeof(shotclockData));

  radio.openWritingPipe(ADDRESS_SHOTCLOCK_1);
  success &= radio.write(&shotclockData, sizeof(shotclockData));

  if (success) {
    digitalWrite(INDICATOR_LED_PIN, HIGH);
  } else {
    digitalWrite(INDICATOR_LED_PIN, LOW);
  }
}

void setup() {
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  digitalWrite(INDICATOR_LED_PIN, LOW);
  
  radio.begin();
  radio.setChannel(CHANNEL_SYSTEM_0);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  game.begin(onDataChangedCallback);

}

void loop() {
  game.loop();
}
