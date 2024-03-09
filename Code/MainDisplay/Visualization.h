#ifndef _VISUALIZATION_h
#define _VISUALIZATION_h
#include <Arduino.h>
#include "DataPackages.h"
class Visualization {
public:
  virtual void begin() = 0;
  virtual void visualize(const MainDisplayData& data);
  //virtual ~Visualization();
};
#endif