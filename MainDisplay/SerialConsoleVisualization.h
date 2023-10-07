#include "Visualization.h"

class SerialConsoleVisualization : public Visualization {
  public:
  virtual void begin();
  virtual void visualizeGameTime(uint16_t gameTime);
  virtual void visualizeScore(uint8_t homeScore, uint8_t awayScore);
  virtual void visualizeHalftime(uint8_t halftime);
};