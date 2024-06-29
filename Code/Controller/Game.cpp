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
  _shotclock.setTimeLeftToShoot(shotclockTimeInSeconds);
  _timeScore.setTimeLeftToPlay(gameTimeInSeconds);
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
  _shotclock.on200msPassed();
  _timeScore.on200msPassed();
  _callback();
}

void Game::on1000msPassed() {
  if (!_isPaused) {
    _timeScore.on1000msPassed();
    _shotclock.on1000msPassed();
    _callback();
  }
}

void Game::setTimeLeftToPlay(uint16_t timeInSeconds) {
  _timeScore.setTimeLeftToPlay(timeInSeconds);
  _isPaused = true;
  _callback();
}

void Game::setTimeLeftToShoot(uint8_t timeInSeconds) {
  _shotclock.setTimeLeftToShoot(timeInSeconds);
  _callback();
}

void Game::increaseHomeScore() {
  _timeScore.increaseHomeScore();
  _callback();
}

void Game::decreaseHomeScore() {
  _timeScore.decreaseHomeScore();
  _callback();
}
void Game::increaseAwayScore() {
  _timeScore.increaseAwayScore();
  _callback();
}
void Game::decreaseAwayScore() {
  _timeScore.decreaseAwayScore();
  _callback();
}
void Game::decreaseHalfTime() {
  _timeScore.decreaseHalfTime();
  _callback();
}
void Game::increaseHalfTime() {
  _timeScore.increaseHalfTime();
  _callback();
}

void Game::playPause() {
  _isPaused = !_isPaused;
}

void Game::enableDisableShotclock() {
  _shotclock.enableDisableShotclock();
  _callback();
}

uint16_t Game::getTimeLeftToPlay() {
  return _timeScore.getTimeLeftToPlay();
}

uint8_t Game::getHomeScore() {
  return _timeScore.getHomeScore();
}

uint8_t Game::getAwayScore() {
  return _timeScore.getAwayScore();
}

uint8_t Game::getHalfTime() {
  return _timeScore.getHalfTime();
}

uint8_t Game::getTimeLeftToShoot() {
  return _shotclock.getTimeLeftToShoot();
}

bool Game::isShotclockVisible() {
  return _shotclock.isShotclockShown();
}

bool Game::isShotclockBeep() {
  return _shotclock.isShotclockBeeping();
}

bool Game::isTimeVisible() {
  return _timeScore.isTimeShown();
}
