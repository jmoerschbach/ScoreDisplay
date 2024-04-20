#ifndef _SEVENSEGMENTVISUALIZATION_h
#define _SEVENSEGMENTVISUALIZATION_h
#include "SevenSegmentDigit.h"
#include "DataPackages.h"
#include "Utils.h"
#include <FastLED.h>

#define LEDS_PER_SEGMENT_TIME 8
#define NUMBER_DIGITS_TIME 2
#define NUMBER_LEDS_TIME (7 * LEDS_PER_SEGMENT_TIME * NUMBER_DIGITS_TIME)
#define DATA_PIN_LEDS_TIME A1


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
