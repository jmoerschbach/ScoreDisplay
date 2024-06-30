#ifndef _UTILS_H
#define _UTILS_H
#include <stdint.h>


constexpr uint8_t ADDRESS_SHOTCLOCK_0[6] = "SHOT0";
constexpr uint8_t ADDRESS_SHOTCLOCK_1[6] = "SHOT1";
constexpr uint8_t ADDRESS_MAIN_DISPLAY[6] = "MAIN0";

/**
* This is the frequenzy offset of system 0
*
* The frequenzy must be the same for all 3 components of a system:
* MainDisplay, Shotclocks, Controller
*
* It must be different between 2 systems
*/
constexpr int CHANNEL_SYSTEM_0 = 110;
/**
* This is the frequenzy offset of system 1
*
* The frequenzy must be the same for all 3 components of a system:
* MainDisplay, Shotclocks, Controller
*
* It must be different between 2 systems
*/
constexpr int CHANNEL_SYSTEM_1 = 115;

typedef struct TwoDigit {
  uint8_t firstDigit;
  uint8_t secondDigit;
} TwoDigit;

TwoDigit convert2DecimalDigit(uint8_t value);

#endif