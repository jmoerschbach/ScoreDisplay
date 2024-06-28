#include "TimeScoreLogic.h"

TimeScore::TimeScore()
  : _timeLeftToPlay(10 * 60), _homeScore(0), _awayScore(0), _halfTime(1) {
}

void TimeScore::on1000msPassed() {
  if (_timeLeftToPlay > 0) {
    _timeLeftToPlay--;
  }
}

void TimeScore::setTimeLeftToPlay(uint16_t timeInSeconds) {
  _timeLeftToPlay = timeInSeconds;
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