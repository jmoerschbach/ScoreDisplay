#ifndef _UTILS_H
#define _UTILS_H
#include <Arduino.h>

typedef struct TwoDigit {
  uint8_t firstDigit;
  uint8_t secondDigit;
} TwoDigit;

TwoDigit convert2DecimalDigit(uint8_t value);
#endif