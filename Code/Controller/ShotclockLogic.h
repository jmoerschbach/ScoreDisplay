#ifndef _SHOTCLOCKLOGIC_h
#define _SHOTCLOCKLOGIC_h
#include <stdint.h>

#include "GameMode.h"

class Shotclock {
public:
  Shotclock::Shotclock();
  void on200msPassed();
  void on1000msPassed();
  void enableDisableShotclock();
  void setTimeLeftToShoot(uint8_t time);
  uint8_t getTimeLeftToShoot();
  bool isShotclockShown();
  bool isShotclockBeeping();
  void Shotclock::setMode(GameMode newMode);

private:
  void flashIfNeeded();
  void beepIfNeeded();
  uint8_t _timeLeftToShoot;
  bool _isShotclockEnabled;
  bool _showShotclock;
  uint8_t _shotclockBlinkCounter;
  bool _beepShotclock;
  uint8_t _shotclockBeepCounter;
  uint8_t _manualSettingBlinkCounter;
  GameMode _mode;
};
#endif