#include "ButtonConfiguration.h"
#include "Game.h"
extern Game game;

GenericButtonConfiguration::GenericButtonConfiguration(
  int pin, ClickAction singleClickAction, ClickAction longPressRepeatAction = []() {}, ClickAction longPressAction = []() {}) {
  _pin = pin;
  _singleClickAction = singleClickAction;
  _longPressRepeatAction = longPressRepeatAction;
  _longPressAction = longPressAction;
}
void GenericButtonConfiguration::event(SmartButton *button, SmartButton::Event event, int clickCounter) {
  if (event == SmartButton::Event::CLICK) {
    _singleClickAction();
  } else if (event == SmartButton::Event::HOLD) {
    _longPressAction();
  } else if (event == SmartButton::Event::HOLD_REPEAT || event == SmartButton::Event::LONG_HOLD_REPEAT) {
    _longPressRepeatAction();
  }
}

bool GenericButtonConfiguration::isPressed(SmartButton *button) {
  return (digitalRead(_pin) == LOW) ? true : false;
}

//########## Button behaviour definition starts here ##########
GenericButtonConfiguration playPause = GenericButtonConfiguration(
  BTN_PLAY_PAUSE_PIN, []() {
    game.playPause();
  },
  []() {}, []() {
    game.toggleMode();
  });

GenericButtonConfiguration shotClock = GenericButtonConfiguration(
  BTN_SHOTCLOCK_RESET_PIN, []() {
    game.setTimeLeftToShoot(60);
  },
  []() {}, []() {
    game.enableDisableShotclock();
  });

GenericButtonConfiguration homeScoreIncrease = SingleClickRepeatButtonConfiguration(
  BTN_HOME_INCREASE_PIN, []() {
    game.increaseHomeScore();
  });

GenericButtonConfiguration homeScoreDecrease = SingleClickRepeatButtonConfiguration(
  BTN_HOME_DECREASE_PIN, []() {
    game.decreaseHomeScore();
  });

GenericButtonConfiguration awayScoreIncrease = SingleClickRepeatButtonConfiguration(
  BTN_AWAY_INCREASE_PIN, []() {
    game.increaseAwayScore();
  });

GenericButtonConfiguration awayScoreDecrease = SingleClickRepeatButtonConfiguration(
  BTN_AWAY_DECREASE_PIN, []() {
    game.decreaseAwayScore();
  });

GenericButtonConfiguration halfTimeIncrease = SingleClickRepeatButtonConfiguration(
  BTN_HALFTIME_INCREASE_PIN, []() {
    game.increaseHalfTime();
  });

GenericButtonConfiguration halfTimeDecrease = SingleClickRepeatButtonConfiguration(
  BTN_HALFTIME_DECREASE_PIN, []() {
    game.decreaseHalfTime();
  });


GenericButtonConfiguration time10Min = SingleClickButtonConfiguration(
  BTN_TIME_10_PIN, []() {
    game.setTimeLeftToPlay(10 * 60);
  });

GenericButtonConfiguration time7_5Min = SingleClickButtonConfiguration(
  BTN_TIME_7_5_PIN, []() {
    game.setTimeLeftToPlay(7 * 60 + 30);
  });

GenericButtonConfiguration time5Min = SingleClickButtonConfiguration(
  BTN_TIME_5_PIN, []() {
    game.setTimeLeftToPlay(5 * 60);
  });

GenericButtonConfiguration time3Min = SingleClickButtonConfiguration(
  BTN_TIME_3_PIN, []() {
    game.setTimeLeftToPlay(3 * 60);
  });

SmartButton btnPlayPause(&playPause);
SmartButton btnShotclockReset(&shotClock);
SmartButton btnHomeIncrease(&homeScoreIncrease);
SmartButton btnHomeDecrease(&homeScoreDecrease);
SmartButton btnAwayIncrease(&awayScoreIncrease);
SmartButton btnAwayDecrease(&awayScoreDecrease);
SmartButton btnHalftimeIncease(&halfTimeIncrease);
SmartButton btnHalftimeDecrease(&halfTimeDecrease);
SmartButton btnTime10(&time10Min);
SmartButton btnTime7_5(&time7_5Min);
SmartButton btnTime5(&time5Min);
SmartButton btnTime3(&time3Min);

void configureButtons() {
  pinMode(BTN_SHOTCLOCK_RESET_PIN, INPUT_PULLUP);
  pinMode(BTN_PLAY_PAUSE_PIN, INPUT_PULLUP);
  pinMode(BTN_HOME_INCREASE_PIN, INPUT_PULLUP);
  pinMode(BTN_HOME_DECREASE_PIN, INPUT_PULLUP);
  pinMode(BTN_AWAY_INCREASE_PIN, INPUT_PULLUP);
  pinMode(BTN_AWAY_DECREASE_PIN, INPUT_PULLUP);
  pinMode(BTN_HALFTIME_INCREASE_PIN, INPUT_PULLUP);
  pinMode(BTN_HALFTIME_DECREASE_PIN, INPUT_PULLUP);

  pinMode(BTN_TIME_10_PIN, INPUT_PULLUP);
  pinMode(BTN_TIME_7_5_PIN, INPUT_PULLUP);
  pinMode(BTN_TIME_5_PIN, INPUT_PULLUP);
  pinMode(BTN_TIME_3_PIN, INPUT_PULLUP);

  btnPlayPause.begin();
  btnShotclockReset.begin();
  btnHomeIncrease.begin();
  btnHomeDecrease.begin();
  btnAwayIncrease.begin();
  btnAwayDecrease.begin();
  btnHalftimeIncease.begin();
  btnHalftimeDecrease.begin();
  btnTime10.begin();
  btnTime7_5.begin();
  btnTime5.begin();
  btnTime3.begin();
}