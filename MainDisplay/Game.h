#ifndef _GAME_h
#define _GAME_h
#include <Arduino.h>
#include "Visualization.h"

class Game {
public:
  Game(Visualization* visualization, uint16_t timeInSeconds = 10 * 60);
  void begin();
  void setTimeLeftToPlay(uint16_t timeInSeconds);
  void increaseHomeScore();
  void decreaseHomeScore();
  void increaseAwayScore();
  void decreaseAwayScore();
  void increaseHalfTime();
  void decreaseHalfTime();
  void pause();
  void resume();

private:
  Visualization* _visualization;
  uint16_t _timeLeftToPlay;
  uint8_t _homeScore;
  uint8_t _awayScore;
  uint8_t _halfTime;

  void showOnDisplay();
};

#endif