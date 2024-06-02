#include "Game.h"
#define PRELOAD_VALUE (65535 - 15625)

volatile uint8_t tick = 0;

ISR(TIMER1_OVF_vect) {
  TCNT1 = PRELOAD_VALUE;
  tick = 1;
}

void configureTimer() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = PRELOAD_VALUE;   // preload counter value for 1Hz
  TIMSK1 |= (1 << TOIE1);  // enable timer overflow interrupt
  sei();
}

void startTimer() {
  TCCR1B |= (1 << CS12) | (1 << CS10);  // Set prescaler to 1024 which starts the timer
}

void stopTimer() {
  TCCR1B &= ~(1 << CS12) & ~(1 << CS10);  // Unset prescaler to stop the timer
}

Game::Game(uint16_t gameTimeInSeconds, uint8_t shotclockTimeInSeconds) {
  _timeLeftToPlay = gameTimeInSeconds;
  _timeLeftToShoot = shotclockTimeInSeconds;
  _awayScore = 0;
  _homeScore = 0;
  _halfTime = 1;
}

void Game::begin(OnDataChanged callback) {
  _callback = callback;
  configureTimer();
  startTimer();
}

void Game::loop() {
  if (tick) {
    tick = 0;
    if (_timeLeftToPlay > 0) {
      _timeLeftToPlay--;
    }
    if (_timeLeftToShoot > 0) {
      _timeLeftToShoot--;
    }
    _callback();
  }
}

void Game::setTimeLeftToPlay(uint16_t timeInSeconds) {
  _timeLeftToPlay = timeInSeconds;
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
void Game::pause() {
  stopTimer();
}
void Game::resume() {
  startTimer();
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
  return _timeLeftToShoot;
}
