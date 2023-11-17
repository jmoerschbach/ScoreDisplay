#ifndef _VISUALIZATION_h
#define _VISUALIZATION_h
#include <Arduino.h>
class Game;
class Visualization {
public:
  virtual void begin() = 0;
  virtual void visualize(const Game& g);
  //virtual ~Visualization();
};
#endif