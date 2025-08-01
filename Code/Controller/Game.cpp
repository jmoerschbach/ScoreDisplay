#include "Game.h"

constexpr int COMPARE_MATCH_1s = 62500;     // 1 * CLK_FREQ / PRESCALER
constexpr int COMPARE_MATCH_200ms = 12500;  // 0.2 * CLK_FREQ / PRESCALER

volatile bool tick_1s = false;
volatile bool tick_200ms = false;
volatile uint16_t timer_counter = 0;

ISR(TIMER1_COMPA_vect) {
  timer_counter++;
  // Every interrupt (200ms base)
  tick_200ms = true;

  if (timer_counter >= 5) {  // Every 5th interrupt (1000ms)
    timer_counter = 0;
    tick_1s = true;
  }
}


void configureTimer() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= B00000100;          // Prescaler = 256

  // Set up CTC mode (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);       // CTC mode

  OCR1A = COMPARE_MATCH_200ms;  // Timer Compare1A Register for 200ms
  TIMSK1 |= B00000010;          // Enable Timer COMPA Interrupt

  // Remove Timer1B interrupt since we're using a counter approach
  sei();
}

Game::Game(uint16_t gameTimeInSeconds, uint8_t shotclockTimeInSeconds)
  : _isPaused(true), _mode(NORMAL) {
  _shotclock.setTimeLeftToShoot(shotclockTimeInSeconds);
  _timeScore.setTimeLeftToPlay(gameTimeInSeconds);
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
  }
}

void Game::setTimeLeftToPlay(uint16_t timeInSeconds) {
  if (_isPaused || _timeScore.getTimeLeftToPlay() == 0) {
    _timeScore.setTimeLeftToPlay(timeInSeconds);
    _isPaused = true;
  }
}

void Game::setTimeLeftToShoot(uint8_t timeInSeconds) {
  _shotclock.setTimeLeftToShoot(timeInSeconds);
}

void Game::increaseHomeScore() {
  if (_mode == MANUAL_TIME_SETTING) {
    _timeScore.setTimeLeftToPlay(_timeScore.getTimeLeftToPlay() + 60);
  } else {
    _timeScore.increaseHomeScore();
  }
}

void Game::decreaseHomeScore() {
  if (_mode == MANUAL_TIME_SETTING) {
    if (_timeScore.getTimeLeftToPlay() > 60) {
      _timeScore.setTimeLeftToPlay(_timeScore.getTimeLeftToPlay() - 60);
    } else {
      _timeScore.setTimeLeftToPlay(0);
    }
  } else {
    _timeScore.decreaseHomeScore();
  }
}
void Game::increaseAwayScore() {
  if (_mode == MANUAL_TIME_SETTING) {
    _timeScore.setTimeLeftToPlay(_timeScore.getTimeLeftToPlay() + 1);
  } else {
    _timeScore.increaseAwayScore();
  }
}
void Game::decreaseAwayScore() {
  if (_mode == MANUAL_TIME_SETTING) {
    if (_timeScore.getTimeLeftToPlay() > 0) {
      _timeScore.setTimeLeftToPlay(_timeScore.getTimeLeftToPlay() - 1);
    }
  } else {
    _timeScore.decreaseAwayScore();
  }
}
void Game::decreaseHalfTime() {
  if (_mode == MANUAL_TIME_SETTING) {
    if (_shotclock.getTimeLeftToShoot() > 0) {
      _shotclock.setTimeLeftToShoot(_shotclock.getTimeLeftToShoot() - 1);
    }
  } else {
    _timeScore.decreaseHalfTime();
  }
}
void Game::increaseHalfTime() {
  if (_mode == MANUAL_TIME_SETTING) {
    _shotclock.setTimeLeftToShoot(_shotclock.getTimeLeftToShoot() + 1);
  } else {
    _timeScore.increaseHalfTime();
  }
}

void Game::playPause() {
  if (_mode == NORMAL) {
    _isPaused = !_isPaused;
  }
}

void Game::toggleMode() {
  _isPaused = true;
  if (_mode == NORMAL) {
    _mode = MANUAL_TIME_SETTING;
  } else {
    _mode = NORMAL;
    if (_timeScore.getTimeLeftToPlay() < 60) {
      _shotclock.setTimeLeftToShoot(_timeScore.getTimeLeftToPlay());
    }
  }
  _timeScore.setMode(_mode);
  _shotclock.setMode(_mode);
}

void Game::enableDisableShotclock() {
  _shotclock.enableDisableShotclock();
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

bool Game::isBeep() {
  return _timeScore.isBeeping();
}
