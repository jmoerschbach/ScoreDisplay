#ifndef _UTILS_H
#define _UTILS_H
#include <Arduino.h>

constexpr byte ADDRESS_SHOTCLOCK_0[6] = "SHOT0";
constexpr byte ADDRESS_SHOTCLOCK_1[6] = "SHOT1";
constexpr byte ADDRESS_MAINDISPLAY[6] = "MAIN";

/**
* This is the frequenzy offset of system 0
*
* The frequenzy must be the same for all 3 components of a system:
* MainDisplay, Shotclocks, Controller
*
* It must be different between 2 systems
*/
constexpr int CHANNEL_SYSTEM_0 = 76;
/**
* This is the frequenzy offset of system 1
*
* The frequenzy must be the same for all 3 components of a system:
* MainDisplay, Shotclocks, Controller
*
* It must be different between 2 systems
*/
constexpr int CHANNEL_SYSTEM_1 = 78;

typedef struct TwoDigit {
  uint8_t firstDigit;
  uint8_t secondDigit;
} TwoDigit;

TwoDigit convert2DecimalDigit(uint8_t value);
#endif