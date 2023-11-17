#include "SerialConsoleVisualization.h"
#include <Arduino.h>

void SerialConsoleVisualization::begin() {
  Serial.begin(9600);
}

void SerialConsoleVisualization::visualize(const Game& g) {
  Serial.print("Seconds left to play: ");
  Serial.println(g.getTimeLeftToPlay());
  Serial.print("Score is ");
  Serial.print(g.getHomeScore());
  Serial.print(":");
  Serial.println(g.getAwayScore());
  Serial.println("-------");
}
