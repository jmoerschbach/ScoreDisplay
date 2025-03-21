#ifndef _TIMESCORELOGIC_h
#define _TIMESCORELOGIC_h
#include <stdint.h>

#include "GameMode.h"

class TimeScore {
public:
  TimeScore::TimeScore();
  void on1000msPassed();
  void on200msPassed();
  void setTimeLeftToPlay(uint16_t timeInSeconds);
  void increaseHomeScore();
  void decreaseHomeScore();
  void increaseAwayScore();
  void decreaseAwayScore();
  void decreaseHalfTime();
  void increaseHalfTime();
  void setMode(GameMode newMode);

  uint16_t getTimeLeftToPlay();
  uint8_t getHomeScore();
  uint8_t getAwayScore();
  uint8_t getHalfTime();
  bool isTimeShown();
  bool isBeeping();
private:
  void flashIfNeeded();
  void beepIfNeeded();
  uint16_t _timeLeftToPlay;
  uint8_t _homeScore;
  uint8_t _awayScore;
  uint8_t _halfTime;
  bool _showTime;
  uint8_t _timeBlinkCounter;
  bool _beep;
  uint8_t _beepCounter;
  uint8_t _manualSettingBlinkCounter;
  GameMode _mode;
};

#endif