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

Game::Game(Visualization* visualization, uint16_t timeInSeconds) {
  _visualization = visualization;
  _timeLeftToPlay = timeInSeconds;
  _awayScore = 0;
  _homeScore = 0;
  _halfTime = 1;
}

void Game::begin() {
  configureTimer();
}

void Game::run() {
  if (tick) {
    tick = 0;
    if (_timeLeftToPlay > 0) {
      _timeLeftToPlay--;
      showOnDisplay();
    }
  }
}

void Game::setTimeLeftToPlay(uint16_t timeInSeconds) {
  _timeLeftToPlay = timeInSeconds;
  showOnDisplay();
}
void Game::increaseHomeScore() {
  _homeScore++;
  showOnDisplay();
}
void Game::decreaseHomeScore() {
  _homeScore--;
  showOnDisplay();
}
void Game::increaseAwayScore() {
  _awayScore++;
  showOnDisplay();
}
void Game::decreaseAwayScore() {
  _awayScore--;
  showOnDisplay();
}
void Game::decreaseHalfTime() {
  if (_halfTime > 1) _halfTime--;
  showOnDisplay();
}
void Game::increaseHalfTime() {
  if (_halfTime < 9) _halfTime++;
  showOnDisplay();
}
void Game::pause() {
  stopTimer();
}
void Game::resume() {
  startTimer();
}
void Game::showOnDisplay() {
  _visualization->visualize(*this);
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
