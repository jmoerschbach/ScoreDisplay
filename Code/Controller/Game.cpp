#include "Game.h"

constexpr int COMPARE_MATCH_1s = 62500;     // 1 * CLK_FREQ / PRESCALER
constexpr int COMPARE_MATCH_200ms = 12500;  // 0.2 * CLK_FREQ / PRESCALER

volatile bool tick_1s = false;
volatile bool tick_200ms = false;


ISR(TIMER1_COMPA_vect) {
  OCR1A += COMPARE_MATCH_200ms;
  tick_200ms = true;
}

ISR(TIMER1_COMPB_vect) {
  OCR1B += COMPARE_MATCH_1s;
  tick_1s = true;
}


void configureTimer() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= B00000100;          // Prescaler = 256
  OCR1A = COMPARE_MATCH_200ms;  // Timer Compare1A Register
  TIMSK1 |= B00000010;          // Enable Timer COMPA Interrupt
  OCR1B = COMPARE_MATCH_1s;     // Timer Compare1B Register
  TIMSK1 |= B00000100;          // Enable Timer COMPB Interrupt
  sei();
}

Game::Game(uint16_t gameTimeInSeconds, uint8_t shotclockTimeInSeconds) {
  shotclock.setTimeLeftToShoot(shotclockTimeInSeconds);
  _timeLeftToPlay = gameTimeInSeconds;
  _awayScore = 0;
  _homeScore = 0;
  _halfTime = 1;
  _isPaused = true;
}

void Game::begin(OnDataChanged callback) {
  _callback = callback;
  configureTimer();
}

void Game::loop() {
  if (tick_200ms) {
    tick_200ms = false;
    on200msPassed();
  }
  if (tick_1s) {
    tick_1s = false;
    on1000msPassed();
  }
}

void Game::on200msPassed() {
  shotclock.on200msPassed();
  _callback();
}

void Game::on1000msPassed() {
  if (!_isPaused) {
    if (_timeLeftToPlay > 0) {
      _timeLeftToPlay--;
    }
    shotclock.on1000msPassed();
    _callback();
  }
}

void Game::setTimeLeftToPlay(uint16_t timeInSeconds) {
  _timeLeftToPlay = timeInSeconds;
  _callback();
}

void Game::setTimeLeftToShoot(uint8_t timeInSeconds) {
  shotclock.setTimeLeftToShoot(timeInSeconds);
  _callback();
}

void Game::increaseHomeScore() {
  if (_homeScore < 99) {
    _homeScore++;
    _callback();
  }
}

void Game::decreaseHomeScore() {
  if (_homeScore > 0) {
    _homeScore--;
    _callback();
  }
}
void Game::increaseAwayScore() {
  if (_awayScore < 99) {
    _awayScore++;
    _callback();
  }
}
void Game::decreaseAwayScore() {
  if (_awayScore > 0) {
    _awayScore--;
    _callback();
  }
}
void Game::decreaseHalfTime() {
  if (_halfTime > 1) {
    _halfTime--;
    _callback();
  }
}
void Game::increaseHalfTime() {
  if (_halfTime < 9) {
    _halfTime++;
    _callback();
  }
}

void Game::playPause() {
  _isPaused = !_isPaused;
}

void Game::enableDisableShotclock() {
  shotclock.enableDisableShotclock();
  _callback();
}

uint16_t Game::getTimeLeftToPlay() {
  return _timeLeftToPlay;
}

uint8_t Game::getHomeScore() {
  return _homeScore;
}

uint8_t Game::getAwayScore() {
  return _awayScore;
}

uint8_t Game::getHalfTime() {
  return _halfTime;
}

uint8_t Game::getTimeLeftToShoot() {
  return shotclock.getTimeLeftToShoot();
}

bool Game::isShotclockVisible() {
  return shotclock.isShotclockShown();
}

bool Game::isShotclockBeep() {
  return shotclock.isShotclockBeeping();
}
