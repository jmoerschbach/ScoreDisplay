#include "SevenSegmentVisualization.h"
#include "Utils.h"
#include <Arduino.h>

void SevenSegmentVisualization::begin() {
  FastLED.addLeds<WS2812B, DATA_PIN_LEDS_TIME, GRB>(_timeLeds, NUMBER_LEDS_TIME);

  FastLED.setBrightness(60);
}
void SevenSegmentVisualization::visualize(const ShotclockData& data) {
  updateTime(data);
  FastLED.show();
}

void SevenSegmentVisualization::updateTime(const ShotclockData& data) {
  if (!data.enabled) {
    _timeDigit_0.hide(&_timeLeds[0 * 7 * LEDS_PER_SEGMENT_TIME]);
    _timeDigit_1.hide(&_timeLeds[1 * 7 * LEDS_PER_SEGMENT_TIME]);
    return;
  }

  TwoDigit secondDigits = convert2DecimalDigit(data.secondsToShot);

  _timeDigit_0.setColor(data.timeColor);
  _timeDigit_1.setColor(data.timeColor);

  _timeDigit_0.show(&_timeLeds[0 * 7 * LEDS_PER_SEGMENT_TIME], secondDigits.secondDigit);
  _timeDigit_1.show(&_timeLeds[1 * 7 * LEDS_PER_SEGMENT_TIME], secondDigits.firstDigit);
}
