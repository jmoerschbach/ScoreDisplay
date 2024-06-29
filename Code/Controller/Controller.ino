#include <Arduino.h>
#include <RF24.h>
#include "ButtonConfiguration.h"
#include "DataPackages.h"
#include "Game.h"
#include "Utils.h"

constexpr int INDICATOR_LED_PIN = 1;
constexpr int BUZZER_PIN = A0;

RF24 radio(9, 10);                // CE, CSN
MainDisplayData mainDisplayData;  //datastructure sent to the main display
ShotclockData shotclockData;      //datastructure sent to the shotclock displays
Game game;


void onDataChangedCallback() {
  // mainDisplayData.brightness = 255;
  mainDisplayData.homeScore = game.getHomeScore();
  mainDisplayData.awayScore = game.getAwayScore();
  mainDisplayData.secondsToPlay = game.getTimeLeftToPlay();
  mainDisplayData.halftime = game.getHalfTime();
  mainDisplayData.showTime = game.isTimeVisible();

  shotclockData.secondsToShot = game.getTimeLeftToShoot();
  shotclockData.enabled = game.isShotclockVisible();
  shotclockData.beep = game.isShotclockBeep();

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
  configureButtons();
  pinMode(INDICATOR_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);


  digitalWrite(INDICATOR_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  radio.begin();
  radio.setChannel(CHANNEL_SYSTEM_0);
  // radio.setChannel(CHANNEL_SYSTEM_1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  game.begin(onDataChangedCallback);

}

void loop() {
  SmartButton::service();
  game.loop();
}
