#ifndef _VISUALIZATION_h
#define _VISUALIZATION_h
#include <Arduino.h>
class Visualization {
public:
  virtual void begin() = 0;
  virtual void visualizeGameTime(uint16_t gameTime) = 0;
  virtual void visualizeScore(uint8_t homeScore, uint8_t awayScore) = 0;
  virtual void visualizeHalftime(uint8_t halftime) = 0;
  //virtual ~Visualization();
};
#endif