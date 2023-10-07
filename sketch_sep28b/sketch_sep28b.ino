#include <FastLED.h>
#define NUM_LEDS 5
#define DATA_PIN 3
CRGB leds[NUM_LEDS];
uint8_t hue = 0;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
}

void loop() {
  fill_rainbow(leds, NUM_LEDS, hue++);
  FastLED.show();
  delay(100);
}
