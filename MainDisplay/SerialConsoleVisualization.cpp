#include "SerialConsoleVisualization.h"
#include <Arduino.h>

void SerialConsoleVisualization::begin() {
  Serial.begin(9600);
}
void SerialConsoleVisualization::visualizeGameTime(uint16_t gameTime) {
}

void SerialConsoleVisualization::visualizeScore(uint8_t homeScore, uint8_t awayScore) {
  Serial.print("Score is ");
  Serial.print(homeScore);
  Serial.print(":");
  Serial.println(awayScore);
}
void SerialConsoleVisualization::visualizeHalftime(uint8_t halftime) {
}