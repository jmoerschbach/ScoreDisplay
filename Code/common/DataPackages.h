#ifndef _DATAPACKAGES_H
#define _DATAPACKAGES_H
#include <FastLED.h>

// This defines the data package sent to the main display
struct MainDisplayData {
  uint16_t secondsToPlay = 0;
  uint8_t awayScore = 0;
  uint8_t homeScore = 0;
  uint8_t halftime = 0;
  CRGB timeColor = CRGB::Red;
  CRGB awayScoreColor = CRGB::Blue;
  CRGB homeScoreColor = CRGB::Green;
  CRGB halftimeColor = CRGB::White;
  uint8_t brightness = 128;
};

// This defines the data packages to the shotclock displays
struct ShotclockData {
  uint8_t secondsToShot = 0;
  bool enabled = true;
  CRGB timeColor = CRGB::Red;
};

#endif