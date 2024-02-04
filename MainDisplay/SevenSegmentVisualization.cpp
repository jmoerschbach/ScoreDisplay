#include "SevenSegmentVisualization.h"
#include <Arduino.h>



void SevenSegmentVisualization::begin() {
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_TIME, GRB>(_timeLeds, NUMBER_LEDS_TIME);
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_SCORE, GRB>(_scoreLeds, NUMBER_LEDS_SCORE);
}
void SevenSegmentVisualization::visualize(const GameData& data) {
  _timeDigit_0.show(&_timeLeds[0 * 7 * LEDS_PER_SEGMENT_TIME], data.secondsToPlay);
  _timeDigit_1.show(&_timeLeds[1 * 7 * LEDS_PER_SEGMENT_TIME], 1);
  _timeDigit_2.show(&_timeLeds[2 * 7 * LEDS_PER_SEGMENT_TIME + 2 * LEDS_PER_DOT], 2);
  _timeDigit_3.show(&_timeLeds[3 * 7 * LEDS_PER_SEGMENT_TIME + 2 * LEDS_PER_DOT], 3);

  _scoreHomeDigit_0.show(&_scoreLeds[0 * 7 * LEDS_PER_SEGMENT_SCORE], 0);
  _scoreHomeDigit_1.show(&_scoreLeds[1 * 7 * LEDS_PER_SEGMENT_SCORE], 0);
  _halftimeDigit.show(&_scoreLeds[2 * 7 * LEDS_PER_SEGMENT_SCORE], 0);
  _scoreAwayDigit_0.show(&_scoreLeds[2 * 7 * LEDS_PER_SEGMENT_SCORE + 1 * 7 * LEDS_PER_SEGMENT_HALFTIME], 0);
  _scoreAwayDigit_1.show(&_scoreLeds[3 * 7 * LEDS_PER_SEGMENT_SCORE + 1 * 7 * LEDS_PER_SEGMENT_HALFTIME], 0);

  FastLED.show();
}
void SevenSegmentVisualization::visualize(const Game& g) {
}


