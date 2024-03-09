#include "SevenSegmentVisualization.h"
#include <Arduino.h>

void SevenSegmentVisualization::begin() {
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_TIME, GRB>(_timeLeds, NUMBER_LEDS_TIME);
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_SCORE, GRB>(_scoreLeds, NUMBER_LEDS_SCORE);

  FastLED.setBrightness(60);
}
void SevenSegmentVisualization::visualize(const MainDisplayData& data) {
  uint8_t minutes = data.secondsToPlay / 60;
  uint8_t seconds = data.secondsToPlay - (minutes * 60);
  TwoDigit minuteDigits = convert2DecimalDigit(minutes);
  TwoDigit secondDigits = convert2DecimalDigit(seconds);

  _timeDigit_0.setColor(data.timeColor);
  _timeDigit_1.setColor(data.timeColor);
  _timeDigit_2.setColor(data.timeColor);
  _timeDigit_3.setColor(data.timeColor);

  _scoreAwayDigit_0.setColor(data.awayScoreColor);
  _scoreAwayDigit_1.setColor(data.awayScoreColor);
  _scoreHomeDigit_0.setColor(data.homeScoreColor);
  _scoreHomeDigit_1.setColor(data.homeScoreColor);

  _halftimeDigit.setColor(data.halftimeColor);

  _timeDigit_0.show(&_timeLeds[0 * 7 * LEDS_PER_SEGMENT_TIME], secondDigits.secondDigit);
  _timeDigit_1.show(&_timeLeds[1 * 7 * LEDS_PER_SEGMENT_TIME], secondDigits.firstDigit);
  for (uint8_t i = 0; i < 2 * LEDS_PER_DOT; i++) {
    _timeLeds[2 * 7 * LEDS_PER_SEGMENT_TIME + i] = data.timeColor;
  }
  _timeDigit_2.show(&_timeLeds[2 * 7 * LEDS_PER_SEGMENT_TIME + 2 * LEDS_PER_DOT], minuteDigits.secondDigit);
  _timeDigit_3.show(&_timeLeds[3 * 7 * LEDS_PER_SEGMENT_TIME + 2 * LEDS_PER_DOT], minuteDigits.firstDigit);


  TwoDigit awayScore = convert2DecimalDigit(data.awayScore);
  _scoreAwayDigit_0.show(&_scoreLeds[0 * 7 * LEDS_PER_SEGMENT_SCORE], awayScore.secondDigit);
  _scoreAwayDigit_1.show(&_scoreLeds[1 * 7 * LEDS_PER_SEGMENT_SCORE], awayScore.firstDigit);
  _halftimeDigit.show(&_scoreLeds[2 * 7 * LEDS_PER_SEGMENT_SCORE], data.halftime);

  TwoDigit homeScore = convert2DecimalDigit(data.homeScore);
  _scoreHomeDigit_0.show(&_scoreLeds[2 * 7 * LEDS_PER_SEGMENT_SCORE + 1 * 7 * LEDS_PER_SEGMENT_HALFTIME], homeScore.secondDigit);
  _scoreHomeDigit_1.show(&_scoreLeds[3 * 7 * LEDS_PER_SEGMENT_SCORE + 1 * 7 * LEDS_PER_SEGMENT_HALFTIME], homeScore.firstDigit);

  FastLED.show();
}

TwoDigit SevenSegmentVisualization::convert2DecimalDigit(uint8_t value) {
  TwoDigit result;
  if (value > 99) {
    result.firstDigit = 10;
    result.firstDigit = 10;
  }
  uint8_t firstDigit = value / 10;
  uint8_t secondDigit = value - (firstDigit * 10);

  result.firstDigit = firstDigit;
  result.secondDigit = secondDigit;
  return result;
}
