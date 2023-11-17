#ifndef _SERIALCONSOLEVISUALIZATION_h
#define _SERIALCONSOLEVISUALIZATION_h
#include "Visualization.h"
#include "Game.h"
class SerialConsoleVisualization : public Visualization {
  public:
  virtual void begin();
  virtual void visualize(const Game& g);
};
#endif