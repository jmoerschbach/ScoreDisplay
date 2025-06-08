#ifndef _DATAPACKAGES_H
#define _DATAPACKAGES_H
#include <stdint.h>
#include "Colors.h"

// This defines the data package sent to the main display
struct MainDisplayData {
  uint16_t secondsToPlay = 0;
  uint8_t awayScore = 0;
  uint8_t homeScore = 0;
  uint8_t halftime = 0;
  bool showTime = true;
  bool enabled = true;
  bool beep = false;
  HTMLColorCode timeColor = Red;
  HTMLColorCode awayScoreColor = Blue;
  HTMLColorCode homeScoreColor = Green;
  HTMLColorCode halftimeColor = White;
  uint8_t brightness = 128;
};

// This defines the data package to the shotclock displays
struct ShotclockData {
  uint8_t secondsToShot = 0;
  bool enabled = true;
  bool beep = false;
  HTMLColorCode timeColor = Red;
  uint8_t brightness = 128;
};

#endif