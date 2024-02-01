#include "SevenSegmentVisualization.h"
#include <Arduino.h>

/*
  bbbbb
  c   a
  c   a
  ggggg
  d   f
  d   f
  eeeee
*/
const uint8_t DIGITS[] = {
  0b00111111,
  0b00100001,
  0b01011011,
  0b01110011,
  0b01100101,
  0b01110110,
  0b01111100,
  0b00100011,
  0b01111111,
  0b01100111
};
void SevenSegmentVisualization::begin() {
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_TIME, GRB>(_timeLeds, NUMBER_LEDS_TIME);
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_SCORE, GRB>(_scoreLeds, NUMBER_LEDS_SCORE);
}
void SevenSegmentVisualization::visualize(uint8_t value) {
  if (value > 9) {
    return;
  }
  uint8_t digit = DIGITS[value];
  for (uint8_t segment = 0; segment < 7; segment++) {
    for (uint8_t j = 0; j < LEDS_PER_SEGMENT_TIME; j++) {
      if (digit & (1 << segment)) {
        _timeLeds[segment * LEDS_PER_SEGMENT_TIME + j] = CRGB::Red;
      } else {
        _timeLeds[segment * LEDS_PER_SEGMENT_TIME + j] = CRGB::Black;
      }
    }
  }

  FastLED.show();
}
void SevenSegmentVisualization::visualize(const Game& g) {
  _timeLeds[0] = CRGB::Red;
  FastLED.show();
}