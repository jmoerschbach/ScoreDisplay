#ifndef _COMMANDS_h
#define _COMMANDS_h
typedef enum {
  ECHO = 0x00,
  PLAY,
  STOP,
  RESET_TIME_10,
  RESET_TIME_7_5,
  RESET_TIME_5,
  RESET_TIME_3,
  INCREASE_HOME_SCORE,
  DECREASE_HOME_SCORE,
  INCREASE_AWAY_SCORE,
  DECREASE_AWAY_SCORE,
  INCREASE_HALFTIME,
  DECREASE_HALFTIME
} command;
#endif