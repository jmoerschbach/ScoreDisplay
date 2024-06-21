#include "Game.h"


constexpr int COMPARE_MATCH_1s = 62500;    // 1 * CLK_FREQ / PRESCALER ;
constexpr int COMPARE_MATCH_100ms = 6250;  // 0.1 * CLK_FREQ / PRESCALER;

volatile bool tick_1s = false;
volatile bool tick_100ms = false;


ISR(TIMER1_COMPA_vect) {
  OCR1A += COMPARE_MATCH_100ms;
  tick_100ms = true;
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
  OCR1A = COMPARE_MATCH_100ms;  // Timer Compare1A Register
  TIMSK1 |= B00000010;          // Enable Timer COMPA Interrupt
  OCR1B = COMPARE_MATCH_1s;     // Timer Compare1B Register
  TIMSK1 |= B00000100;          // Enable Timer COMPB Interrupt
  sei();
}

Game::Game(uint16_t gameTimeInSeconds, uint8_t shotclockTimeInSeconds) {
  _timeLeftToPlay = gameTimeInSeconds;
  _timeLeftToShoot = shotclockTimeInSeconds;
  _awayScore = 0;
  _homeScore = 0;
  _halfTime = 1;
  _isPaused = true;
  _isShotclockEnabled = true;
}

void Game::begin(OnDataChanged callback) {
  _callback = callback;
  configureTimer();
}

void Game::loop() {
  if (tick_100ms) {
    tick_100ms = false;
    on100msPassed();
  }
  if (tick_1s) {
    tick_1s = false;
    on1000msPassed();
  }
}

void Game::on100msPassed() {
}

void Game::on1000msPassed() {
  if (!_isPaused) {
    if (_timeLeftToPlay > 0) {
      _timeLeftToPlay--;
    }
    if (_isShotclockEnabled && _timeLeftToShoot > 0) {
      _timeLeftToShoot--;
    }
    _callback();
  }
}

void Game::setTimeLeftToPlay(uint16_t timeInSeconds) {
  _timeLeftToPlay = timeInSeconds;
  _callback();
}

void Game::setTimeLeftToShoot(uint8_t timeInSeconds) {
  _timeLeftToShoot = timeInSeconds;
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

void Game::toggleShotclock() {
  _isShotclockEnabled = !_isShotclockEnabled;
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
  return _timeLeftToShoot;
}

bool Game::isShotclockEnabled() {
  return _isShotclockEnabled;
}
