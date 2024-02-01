#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <FastLED.h>
#include "Commands.h"
#include "Game.h"
#include "Visualization.h"
#include "SerialConsoleVisualization.h"
#include "SevenSegmentVisualization.h"

RF24 radio(9, 10);  // CE, CSN
SerialConsoleVisualization visualization;
SevenSegmentVisualization visualization2;

Game game(&visualization);

const byte address[6] = "00001";


uint8_t counter = 0;
void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  FastLED.setBrightness(128);
  visualization2.begin();
  game.begin();
  // game.resume();
  // game.pause();
}

void sendEcho() {
  const byte echoCommand = ECHO;
  //configure to send
  //send echo
}

void loop() {
  if (radio.available()) {
    executeCommand();
  }
  if (counter > 9) {
    counter = 0;
  }
  visualization2.visualize(counter++);
  delay(500);
}


void executeCommand() {
  byte receivedCommand;
  radio.read(&receivedCommand, sizeof(receivedCommand));
  Serial.println(receivedCommand);
  switch (receivedCommand) {
    case ECHO:
      sendEcho();
      break;
    case PLAY:
      game.resume();
      break;
    case STOP:
      game.pause();
      break;
    case RESET_TIME_10:
      game.setTimeLeftToPlay(10 * 60);
      break;
    case RESET_TIME_7_5:
      game.setTimeLeftToPlay(7 * 60 + 30);
      break;
    case RESET_TIME_5:
      game.setTimeLeftToPlay(5 * 60);
      break;
    case RESET_TIME_3:
      game.setTimeLeftToPlay(3 * 60);
      break;
    case INCREASE_HOME_SCORE:
      game.increaseHomeScore();
      leds[0] = CRGB::Red;
      break;
    case DECREASE_HOME_SCORE:
      game.decreaseHomeScore();
      leds[0] = CRGB::Red;
      break;
    case INCREASE_AWAY_SCORE:
      game.increaseAwayScore();
      leds[0] = CRGB::Red;
      break;
    case DECREASE_AWAY_SCORE:
      leds[0] = CRGB::Black;
      game.decreaseAwayScore();
      break;
    default:
      leds[0] = CRGB::Black;
  }
}
