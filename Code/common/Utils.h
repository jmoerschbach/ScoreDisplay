#ifndef _UTILS_H
#define _UTILS_H
#include <Arduino.h>

#define ADDRESS_SHOTCLOCK_0 "SHOT0"
#define ADDRESS_SHOTCLOCK_1 "SHOT1"
#define ADDRESS_MAINDISPLAY "MAIN"

typedef struct TwoDigit {
  uint8_t firstDigit;
  uint8_t secondDigit;
} TwoDigit;

TwoDigit convert2DecimalDigit(uint8_t value);
#endif