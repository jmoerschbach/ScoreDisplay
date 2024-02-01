#ifndef _SEVENSEGMENTVISUALIZATION_h
#define _SEVENSEGMENTVISUALIZATION_h
#include "Visualization.h"
#include "Game.h"
#include <FastLED.h>

#define LEDS_PER_SEGMENT_TIME 7
#define NUMBER_DIGITS_TIME 4
#define NUMBER_LEDS_TIME (7 * LEDS_PER_SEGMENT_TIME  * NUMBER_DIGITS_TIME)
#define DATA_PIN_LEDS_TIME A1

#define LEDS_PER_SEGMENT_SCORE 6
#define NUMBER_DIGITS_SCORE 2
#define NUMBER_LEDS_SCORE (LEDS_PER_SEGMENT_SCORE * 7 * NUMBER_DIGITS_SCORE * 2)
#define DATA_PIN_LEDS_SCORE A0
class SevenSegmentVisualization : public Visualization {
  public:
  virtual void begin();
  virtual void visualize(const Game& g);
  void visualize(uint8_t value);
  private:
  CRGB _timeLeds[NUMBER_LEDS_TIME];
  CRGB _scoreLeds[NUMBER_LEDS_SCORE];
};
#endif