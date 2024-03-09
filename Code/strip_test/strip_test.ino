#include <FastLED.h>

#define LEDS_PER_SEGMENT 6
#define NUM_LEDS (4*7*LEDS_PER_SEGMENT + 1*7*4+4)
#define DATA_PIN_LEDS 3

uint8_t hue = 0;
CRGB _leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LEDS>(_leds, NUM_LEDS);
  FastLED.setBrightness(128);

  fill_solid(_leds, NUM_LEDS, CRGB::Red);
  
  // for (uint8_t segment = 0; segment < 7; segment++) {
  //   hue += 200;
  //   for (uint8_t led = 0; led < LEDS_PER_SEGMENT; led++) {
  //     _leds[(segment * LEDS_PER_SEGMENT) + led] = CHSV(hue, 128, 255);
  //   }
  // }
  fill_solid(_leds, NUM_LEDS, CRGB::White);

  FastLED.show();
}
  void loop () {
    uint8_t thisSpeed = 10;
    uint8_t deltaHue= 10;
    uint8_t thisHue = beat8(thisSpeed,255); 
    fill_rainbow(_leds, NUM_LEDS, thisHue, deltaHue);            
   // FastLED.show();

}
