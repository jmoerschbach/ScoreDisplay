#ifndef _SEVENSEGMENTDIGIT_h
#define _SEVENSEGMENTDIGIT_h

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
constexpr uint8_t ZERO    = 0b00111111;
constexpr uint8_t ONE     = 0b00100001;
constexpr uint8_t TWO     = 0b01011011;
constexpr uint8_t THREE   = 0b01110011;
constexpr uint8_t FOUR    = 0b01100101;
constexpr uint8_t FIVE    = 0b01110110;
constexpr uint8_t SIX     = 0b01111100;
constexpr uint8_t SEVEN   = 0b00100011;
constexpr uint8_t EIGHT   = 0b01111111;
constexpr uint8_t NINE    = 0b01100111;
constexpr uint8_t INVALID = 0b01000000;
const uint8_t DIGITS[] = {
  ZERO,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE
};

class SevenSegmentDigit {
  public:
  SevenSegmentDigit(uint8_t ledsPerSegment, CRGB color = CRGB::Red);
  void show(CRGB leds[], uint8_t value);
  void setColor(const CRGB& color);
  
  private:
  uint8_t _ledsPerSegment;
  CRGB _color;
};
#endif