#include "ShotclockLogic.h"
constexpr int SHOTCLOCK_BLINKS = 6;
constexpr int SHOTCLOCK_BEEPS = 5;

Shotclock::Shotclock()
  : _timeLeftToShoot(60), _isShotclockEnabled(true), _showShotclock(true), _shotclockBlinkCounter(SHOTCLOCK_BLINKS), _shotclockBeepCounter(SHOTCLOCK_BEEPS) {
}
void Shotclock::enableDisableShotclock() {
  _isShotclockEnabled = !_isShotclockEnabled;
}

void Shotclock::setTimeLeftToShoot(uint8_t time) {
  _timeLeftToShoot = time;
  _shotclockBlinkCounter = SHOTCLOCK_BLINKS;
  _shotclockBeepCounter = SHOTCLOCK_BEEPS;
}

void Shotclock::on1000msPassed() {
  if (_isShotclockEnabled && _timeLeftToShoot > 0) {
    _timeLeftToShoot--;
  }
}

void Shotclock::on200msPassed() {
  flashIfNeeded();
  beepIfNeeded();
}

void Shotclock::flashIfNeeded() {
  if (_isShotclockEnabled && _timeLeftToShoot == 0 && _shotclockBlinkCounter > 0) {
    _showShotclock = !_showShotclock;
    _shotclockBlinkCounter--;
  }
}

void Shotclock::beepIfNeeded() {
  if (_isShotclockEnabled && _timeLeftToShoot == 0 && _shotclockBeepCounter > 0) {
    _beepShotclock = true;
    _shotclockBeepCounter--;
  } else {
    _beepShotclock = false;
  }
}

uint8_t Shotclock::getTimeLeftToShoot() {
  return _timeLeftToShoot;
}

bool Shotclock::isShotclockShown() {
  return _isShotclockEnabled && _showShotclock;
}

bool Shotclock::isShotclockBeeping() {
  return _isShotclockEnabled && _beepShotclock;
}