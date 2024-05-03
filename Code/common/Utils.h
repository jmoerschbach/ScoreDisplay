#ifndef _UTILS_H
#define _UTILS_H
#include <Arduino.h>

#define ADDRESS_SHOTCLOCK_0 "SHOT0"
#define ADDRESS_SHOTCLOCK_1 "SHOT1"
#define ADDRESS_MAINDISPLAY "MAIN"

// this is the frequenzy offset
// this must be the same for all 3 components of a system:
// MainDisplay, Shotclocks, Controller
// It must be different between 2 systems
constexpr int CHANNEL_SYSTEM_0 = 5;
constexpr int CHANNEL_SYSTEM_1 = 50;

typedef struct TwoDigit {
  uint8_t firstDigit;
  uint8_t secondDigit;
} TwoDigit;

TwoDigit convert2DecimalDigit(uint8_t value);
#endif