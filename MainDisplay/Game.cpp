#include "Game.h"

Game::Game(Visualization* visualization, uint16_t timeInSeconds) {
  _visualization = visualization;
  _timeLeftToPlay = timeInSeconds;
  _awayScore = 0;
  _homeScore = 0;
  _halfTime = 1;
}

void Game::begin() {
  //configure timer?
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
  if(_halfTime > 0) _halfTime--;
  showOnDisplay();
}
void Game::increaseHalfTime() {
  if(_halfTime < 9) _halfTime++;
  showOnDisplay();
}
void Game::pause() {
  //pause timer
}
void Game::resume() {
  //start timer
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
