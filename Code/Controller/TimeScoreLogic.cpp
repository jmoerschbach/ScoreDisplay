#include "TimeScoreLogic.h"

constexpr int TIME_BLINKS = 8;
constexpr int TIME_BEEPS = 1;

constexpr int TIME_MANUAL_BLINKS = 2;

TimeScore::TimeScore()
  : _timeLeftToPlay(10 * 60), _homeScore(0), _awayScore(0), _halfTime(1), _showTime(true), _timeBlinkCounter(TIME_BLINKS), _beep(false), _beepCounter(TIME_BEEPS), _manualSettingBlinkCounter(TIME_MANUAL_BLINKS), _mode(NORMAL) {
}

void TimeScore::on1000msPassed() {
  if (_timeLeftToPlay > 0) {
    _timeLeftToPlay--;
  }
}
void TimeScore::on200msPassed() {
  flashIfNeeded();
  beepIfNeeded();
}
void TimeScore::flashIfNeeded() {
  if (_mode == NORMAL && _timeLeftToPlay == 0 && _timeBlinkCounter > 0) {
    _showTime = !_showTime;
    _timeBlinkCounter--;
  } else if (_mode == MANUAL_TIME_SETTING && _manualSettingBlinkCounter-- == 0) {
    _showTime = !_showTime;
    _manualSettingBlinkCounter = TIME_MANUAL_BLINKS;
  }
}

void TimeScore::beepIfNeeded() {
  if (_mode == NORMAL && _timeLeftToPlay == 0 && _beepCounter > 0) {
    _beep = true;
    _beepCounter--;
  } else {
    _beep = false;
  }
}

void TimeScore::setTimeLeftToPlay(uint16_t timeInSeconds) {
  _timeLeftToPlay = timeInSeconds;
  _timeBlinkCounter = TIME_BLINKS;
  _beepCounter = TIME_BEEPS;
  _beep = false;
  _showTime = true;
}

void TimeScore::increaseHomeScore() {
  if (_homeScore < 99) {
    _homeScore++;
  }
}

void TimeScore::decreaseHomeScore() {
  if (_homeScore > 0) {
    _homeScore--;
  }
}
void TimeScore::increaseAwayScore() {
  if (_awayScore < 99) {
    _awayScore++;
  }
}
void TimeScore::decreaseAwayScore() {
  if (_awayScore > 0) {
    _awayScore--;
  }
}
void TimeScore::decreaseHalfTime() {
  if (_halfTime > 1) {
    _halfTime--;
  }
}
void TimeScore::increaseHalfTime() {
  if (_halfTime < 9) {
    _halfTime++;
  }
}

void TimeScore::setMode(GameMode newMode) {
  _mode = newMode;
  if (_mode == NORMAL) {
    _showTime = true;
  }
}

uint16_t TimeScore::getTimeLeftToPlay() {
  return _timeLeftToPlay;
}

uint8_t TimeScore::getHomeScore() {
  return _homeScore;
}

uint8_t TimeScore::getAwayScore() {
  return _awayScore;
}

uint8_t TimeScore::getHalfTime() {
  return _halfTime;
}

bool TimeScore::isTimeShown() {
  return _showTime;
}

bool TimeScore::isBeeping() {
  return _beep;
}