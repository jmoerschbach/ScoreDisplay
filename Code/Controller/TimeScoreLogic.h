#ifndef _TIMESCORELOGIC_h
#define _TIMESCORELOGIC_h
#include <stdint.h>

class TimeScore {
public:
  TimeScore::TimeScore();
  void on1000msPassed();
  void setTimeLeftToPlay(uint16_t timeInSeconds);
  void increaseHomeScore();
  void decreaseHomeScore();
  void increaseAwayScore();
  void decreaseAwayScore();
  void decreaseHalfTime();
  void increaseHalfTime();

  uint16_t getTimeLeftToPlay();
  uint8_t getHomeScore();
  uint8_t getAwayScore();
  uint8_t getHalfTime();
private:
  uint16_t _timeLeftToPlay;
  uint8_t _homeScore;
  uint8_t _awayScore;
  uint8_t _halfTime;
};

#endif