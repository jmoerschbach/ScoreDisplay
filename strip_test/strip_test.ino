#include <FastLED.h>

#define LEDS_PER_SEGMENT 7
#define NUM_LEDS (LEDS_PER_SEGMENT * 7)
#define DATA_PIN_LEDS 5

uint8_t hue = 0;
CRGB _leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS, GRB>(_leds, NUM_LEDS);
}

void loop() {

  for (uint8_t segment = 0; segment < 7; segment++) {
    hue += 10;
    for (uint8_t led = 0; led < LEDS_PER_SEGMENT, led++;) {
      _leds[(segment * LEDS_PER_SEGMENT) + led] = CHSV(hue, 128, 255);
    }
  }
  delay(200);
  FastLED.show();
}
