#ifndef _SEVENSEGMENTVISUALIZATION_h
#define _SEVENSEGMENTVISUALIZATION_h
#include "Visualization.h"
#include "SevenSegmentDigit.h"
#include "DataPackages.h"
#include <FastLED.h>

#define LEDS_PER_SEGMENT_TIME 7
#define LEDS_PER_DOT 2
#define NUMBER_DIGITS_TIME 4
#define NUMBER_LEDS_TIME (7 * LEDS_PER_SEGMENT_TIME * NUMBER_DIGITS_TIME + 2 * LEDS_PER_DOT)
#define DATA_PIN_LEDS_TIME A1

#define LEDS_PER_SEGMENT_SCORE 6
#define LEDS_PER_SEGMENT_HALFTIME 5
#define NUMBER_DIGITS_SCORE 4
#define NUMBER_LEDS_SCORE (7 * LEDS_PER_SEGMENT_SCORE * NUMBER_DIGITS_SCORE + 7 * LEDS_PER_SEGMENT_HALFTIME)
#define DATA_PIN_LEDS_SCORE A0

struct TwoDigit {
  uint8_t firstDigit;
  uint8_t secondDigit;
};

class SevenSegmentVisualization : public Visualization {
public:
  virtual void begin();
  virtual void visualize(const GameData& data);
private:
  TwoDigit convert2DecimalDigit(uint8_t value);

  SevenSegmentDigit _timeDigit_0 = SevenSegmentDigit(LEDS_PER_SEGMENT_TIME);
  SevenSegmentDigit _timeDigit_1 = SevenSegmentDigit(LEDS_PER_SEGMENT_TIME);
  SevenSegmentDigit _timeDigit_2 = SevenSegmentDigit(LEDS_PER_SEGMENT_TIME);
  SevenSegmentDigit _timeDigit_3 = SevenSegmentDigit(LEDS_PER_SEGMENT_TIME);

  SevenSegmentDigit _scoreHomeDigit_0 = SevenSegmentDigit(LEDS_PER_SEGMENT_SCORE);
  SevenSegmentDigit _scoreHomeDigit_1 = SevenSegmentDigit(LEDS_PER_SEGMENT_SCORE);
  SevenSegmentDigit _scoreAwayDigit_0 = SevenSegmentDigit(LEDS_PER_SEGMENT_SCORE);
  SevenSegmentDigit _scoreAwayDigit_1 = SevenSegmentDigit(LEDS_PER_SEGMENT_SCORE);
  SevenSegmentDigit _halftimeDigit = SevenSegmentDigit(LEDS_PER_SEGMENT_HALFTIME);

  CRGB _timeLeds[NUMBER_LEDS_TIME];
  CRGB _scoreLeds[NUMBER_LEDS_SCORE];
};
#endif