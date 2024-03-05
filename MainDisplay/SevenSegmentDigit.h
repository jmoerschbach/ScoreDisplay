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
constexpr uint8_t ZERO = 0b00111111;
constexpr uint8_t ONE = 0b00111111;
constexpr uint8_t TWO = 0b00111111;
constexpr uint8_t THREE = 0b00111111;
constexpr uint8_t FOUR = 0b00111111;
constexpr uint8_t FIVE = 0b00111111;
constexpr uint8_t SIX = 0b00111111;
constexpr uint8_t SEVEN = 0b00111111;
constexpr uint8_t EIGHT = 0b00111111;
constexpr uint8_t NINE = 0b00111111;
constexpr uint8_t INVALID = 0b00111111;
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
  0b01100111,
  0b01000000 //INVALID, show only segment g
};
class SevenSegmentDigit {
  public:
  SevenSegmentDigit(uint8_t ledsPerSegment, CRGB color = CRGB::Red);
  void show(CRGB leds[], uint8_t value);
  
  private:
  uint8_t _ledsPerSegment;
  CRGB _color;
};
#endif