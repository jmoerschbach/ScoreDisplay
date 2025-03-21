#ifndef _SEVENSEGMENTVISUALIZATION_h
#define _SEVENSEGMENTVISUALIZATION_h
#include <FastLED.h>
#include "Constants.h"
#include "SevenSegmentDigit.h"
#include "DataPackages.h"
#include "Utils.h"

#ifdef LED_DENSITY_LOW
constexpr int LEDS_PER_SEGMENT_TIME = 8;
#else
constexpr int LEDS_PER_SEGMENT_TIME = 11;
#endif

constexpr int NUMBER_DIGITS_TIME = 2;
constexpr int NUMBER_LEDS_TIME = 7 * LEDS_PER_SEGMENT_TIME * NUMBER_DIGITS_TIME;
constexpr int DATA_PIN_LEDS_TIME = A0;


class SevenSegmentVisualization {
public:
  void begin();
  void visualize(const ShotclockData& data);
private:
  void updateTime(const ShotclockData& data);

  SevenSegmentDigit _timeDigit_0 = SevenSegmentDigit(LEDS_PER_SEGMENT_TIME);
  SevenSegmentDigit _timeDigit_1 = SevenSegmentDigit(LEDS_PER_SEGMENT_TIME);


  CRGB _timeLeds[NUMBER_LEDS_TIME];
};
#endif
