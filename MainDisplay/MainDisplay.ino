#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <FastLED.h>
#include "Commands.h"
#include "Game.h"
#include "Visualization.h"
#include "SerialConsoleVisualization.h"

#define NUM_LEDS 5
#define DATA_PIN 3

CRGB leds[NUM_LEDS];
RF24 radio(10, 9);  // CE, CSN
SerialConsoleVisualization visualization;

Game game(&visualization);

const byte address[6] = "00001";



void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
  visualization.begin();
  game.begin();
}

void loop() {
  if (radio.available()) {
    byte text;
    radio.read(&text, sizeof(text));
    if (text == PLAY) {
      leds[0] = CRGB::Red;
      game.increaseHomeScore();
    } else {
      leds[0] = CRGB::Black;
      //game.decreaseHomeScore();
    }
    FastLED.show();
  }
}
