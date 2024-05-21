#include "SevenSegmentDigit.h"

SevenSegmentDigit::SevenSegmentDigit(uint8_t ledsPerSegment, CRGB color) {
  _ledsPerSegment = ledsPerSegment;
  _color = color;
}

void SevenSegmentDigit::show(CRGB leds[], uint8_t value) {
  uint8_t digit = INVALID;
  if (value <= 9) {
    digit = DIGITS[value];
  }
  fill_solid(leds, 7 * _ledsPerSegment, _color);
  for (uint8_t segment = 0; segment < 7; segment++) {
    if (digit & (1 << segment)) {
      //do nothing
    } else {
      fill_solid(&leds[segment * _ledsPerSegment], _ledsPerSegment, CRGB::Black);
    }
  }
}

void SevenSegmentDigit::showRainbow(CRGB leds[], uint8_t value) {
  uint8_t digit = INVALID;
  if (value <= 9) {
    digit = DIGITS[value];
  }
  fill_rainbow(leds, 7 * _ledsPerSegment, 10, 15);
  for (uint8_t segment = 0; segment < 7; segment++) {
    if (digit & (1 << segment)) {
      // do nothing
    } else {
      fill_solid(&leds[segment * _ledsPerSegment], _ledsPerSegment, CRGB::Black);
    }
  }
}

void SevenSegmentDigit::hide(CRGB leds[]) {
  fill_solid(leds, 7 * _ledsPerSegment, CRGB::Black);
}

void SevenSegmentDigit::setColor(const CRGB& color) {
  _color = color;
}
