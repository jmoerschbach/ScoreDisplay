#ifndef _DATAPACKAGES_H
#define _DATAPACKAGES_H
struct GameData {
  uint16_t secondsToPlay;
  uint8_t awayScore;
  uint8_t homeScore;
  uint8_t halftime;
};

struct shotclockData {
  uint8_t secondsToShot;
  bool enabled;
};
#endif