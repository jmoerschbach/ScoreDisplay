#ifndef _CONSTANTS_H
#define _CONSTANTS_H

/**
* Version 1 has a lower number of LEDs (60 Leds/m),
* whereas later versions use more LEDs (96 Leds/m).
*
* Comment out if building for later versions!
*/
//#define LED_DENSITY_LOW

/**
* This decides which frequency is used.
* Multiple systems may run in parallel and must use 
* different frequencies to avoid crosstalk.
* See below definition of CHANNEL.
* 
* Possible values: 0, 1 (may support more in future if needed)
*/
#define SYSTEM 0

/**
* This enables battery monitoring in shotclocks.
* Comment out if building for shotclocks without battery support.
*/
#define BATTERY_POWERED_SHOTCLOCK

/**
* This is the frequenzy offset.
*
* The frequenzy must be the same for all 3 components of a system:
* MainDisplay, Shotclocks, Controller
*
* It must be different between 2 systems
*/
#if SYSTEM == 0
constexpr int CHANNEL = 110;
#elif SYSTEM == 1 
constexpr int CHANNEL = 115;
#endif


/** The address of the first shotclock component */
constexpr uint8_t ADDRESS_SHOTCLOCK_0[6] = "SHOT0";
/** The address of the second shotclock component */
constexpr uint8_t ADDRESS_SHOTCLOCK_1[6] = "SHOT1";
/** The address of the maindisplay component */
constexpr uint8_t ADDRESS_MAIN_DISPLAY[6] = "MAIN0";

#endif