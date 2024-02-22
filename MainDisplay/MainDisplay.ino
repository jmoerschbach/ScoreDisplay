#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <FastLED.h>
#include "Commands.h"
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

  FastLED.setBrightness(128);
  visualization2.begin();

  data.secondsToPlay = 595;
  data.awayScore = 3;
  data.homeScore = 1;
  data.halftime = 1;
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
  // if (counter > 9) {
  //   counter = 0;
  // }
  visualization2.visualize(data);
  delay(500);
}


void executeCommand() {
  byte receivedCommand;
  radio.read(&receivedCommand, sizeof(receivedCommand));
  Serial.println(receivedCommand);
  // switch (receivedCommand) {
  //   case ECHO:
  //     sendEcho();
  //     break;
  //   case PLAY:
  //     game.resume();
  //     break;
  //   case STOP:
  //     game.pause();
  //     break;
  //   case RESET_TIME_10:
  //     game.setTimeLeftToPlay(10 * 60);
  //     break;
  //   case RESET_TIME_7_5:
  //     game.setTimeLeftToPlay(7 * 60 + 30);
  //     break;
  //   case RESET_TIME_5:
  //     game.setTimeLeftToPlay(5 * 60);
  //     break;
  //   case RESET_TIME_3:
  //     game.setTimeLeftToPlay(3 * 60);
  //     break;
  //   case INCREASE_HOME_SCORE:
  //     game.increaseHomeScore();
  //     break;
  //   case DECREASE_HOME_SCORE:
  //     game.decreaseHomeScore();
  //     break;
  //   case INCREASE_AWAY_SCORE:
  //     game.increaseAwayScore();
  //     break;
  //   case DECREASE_AWAY_SCORE:
  //     game.decreaseAwayScore();
  //     break;
  //   default:
  //   ;
  // }
}
