#ifndef _GAME_h
#define _GAME_h
#include <Arduino.h>

using OnDataChanged = void (*)(void);
class Game {
public:
  Game(uint16_t gameTimeInSeconds = 10 * 60, uint8_t shotclockTimeInSeconds = 60);
  void begin(OnDataChanged callback);
  void setTimeLeftToPlay(uint16_t timeInSeconds);
  void increaseHomeScore();
  void decreaseHomeScore();
  void increaseAwayScore();
  void decreaseAwayScore();
  void increaseHalfTime();
  void decreaseHalfTime();
  void playPause();

  void loop();
  void on1000msPassed();
  void on100msPassed();

  uint8_t getHomeScore();
  uint8_t getAwayScore();
  uint8_t getHalfTime();
  uint16_t getTimeLeftToPlay();
  uint8_t getTimeLeftToShoot();

private:
  OnDataChanged _callback;
  uint16_t _timeLeftToPlay;
  uint8_t _timeLeftToShoot;
  uint8_t _homeScore;
  uint8_t _awayScore;
  uint8_t _halfTime;
  bool _isPaused;
};

#endif