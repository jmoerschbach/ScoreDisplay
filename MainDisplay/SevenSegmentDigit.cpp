#include "SevenSegmentDigit.h"


SevenSegmentDigit::SevenSegmentDigit(uint8_t ledsPerSegment) {
  _ledsPerSegment = ledsPerSegment;
}

void SevenSegmentDigit::show(CRGB leds[], uint8_t value) {
  if (value > 9) {
    return;
  }
  uint8_t digit = DIGITS[value];
  for (uint8_t segment = 0; segment < 7; segment++) {
    for (uint8_t j = 0; j < _ledsPerSegment; j++) {
      if (digit & (1 << segment)) {
        leds[segment * _ledsPerSegment + j] = CRGB::Red;
      } else {
        leds[segment * _ledsPerSegment + j] = CRGB::Black;
      }
    }
  }
}