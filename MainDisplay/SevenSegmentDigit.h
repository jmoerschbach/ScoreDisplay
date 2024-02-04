#ifndef _SEVENSEGMENTVDIGIT_h
#define _SEVENSEGMENTVDIGIT_h

#include <FastLED.h>

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
class SevenSegmentDigit {
  public:
  SevenSegmentDigit(uint8_t ledsPerSegment);
  void show(CRGB leds[], uint8_t value);
  
  private:
  uint8_t _ledsPerSegment;
};
#endif