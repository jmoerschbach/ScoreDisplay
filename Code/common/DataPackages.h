#ifndef _DATAPACKAGES_H
#define _DATAPACKAGES_H
#include <FastLED.h>
struct MainDisplayData {
  uint16_t secondsToPlay = 0;
  uint8_t awayScore = 0;
  uint8_t homeScore = 0;
  uint8_t halftime = 0;
  CRGB timeColor = CRGB::Red;
  CRGB awayScoreColor= CRGB::Blue;
  CRGB homeScoreColor = CRGB::Green;
  CRGB halftimeColor = CRGB::White;

};

struct ShotclockData {
  uint8_t secondsToShot;
  bool enabled;
};
#endif