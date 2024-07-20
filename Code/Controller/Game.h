#ifndef _GAME_h
#define _GAME_h
#include <Arduino.h>
#include "ShotclockLogic.h"
#include "TimeScoreLogic.h"
#include "GameMode.h"

using OnDataChanged = void (*)(void);



class Game {
public:
  Game(uint16_t gameTimeInSeconds = 10 * 60, uint8_t shotclockTimeInSeconds = 60);
  void begin(OnDataChanged callback);
  void setTimeLeftToPlay(uint16_t timeInSeconds);
  void setTimeLeftToShoot(uint8_t timeInSeconds);
  void increaseHomeScore();
  void decreaseHomeScore();
  void increaseAwayScore();
  void decreaseAwayScore();
  void increaseHalfTime();
  void decreaseHalfTime();
  void playPause();
  void toggleMode();
  void enableDisableShotclock();

  void loop();
  void on1000msPassed();
  void on200msPassed();

  uint8_t getHomeScore();
  uint8_t getAwayScore();
  uint8_t getHalfTime();
  uint16_t getTimeLeftToPlay();
  uint8_t getTimeLeftToShoot();
  bool shouldShotclockBeep();
  bool isShotclockVisible();
  bool isShotclockBeep();
  bool isTimeVisible();
  bool isBeep();

private:
  OnDataChanged _callback;
  GameMode _mode;
  Shotclock _shotclock;
  TimeScore _timeScore;
  bool _isPaused;
};

#endif