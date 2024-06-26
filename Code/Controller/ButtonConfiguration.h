#include <SmartButton.h>

constexpr int BTN_HOME_INCREASE_PIN = 3;
constexpr int BTN_HOME_DECREASE_PIN = 4;
constexpr int BTN_AWAY_INCREASE_PIN = 5;
constexpr int BTN_AWAY_DECREASE_PIN = 6;
constexpr int BTN_HALFTIME_INCREASE_PIN = 7;
constexpr int BTN_HALFTIME_DECREASE_PIN = 8;

constexpr int BTN_TIME_3_PIN = A3;
constexpr int BTN_TIME_5_PIN = A2;
constexpr int BTN_TIME_7_5_PIN = A5;
constexpr int BTN_TIME_10_PIN = A4;

constexpr int BTN_SHOTCLOCK_RESET_PIN = A1;
constexpr int BTN_PLAY_PAUSE_PIN = 2;

using namespace smartbutton;
using ClickAction = void (*)(void);


/**
* This is a small wrapper class to ease the usage of the SmartButton-Api.
* It offers the possibility to define a button's behavior via lambdas for single click, long press and long press repeat events.
*/
class GenericButtonConfiguration : public SmartButtonInterface {

public:
  GenericButtonConfiguration(
    int pin, ClickAction singleClickAction, ClickAction longPressRepeatAction = []() {}, ClickAction longPressAction = []() {});
  virtual void event(SmartButton *button, SmartButton::Event event, int clickCounter);

  virtual bool isPressed(SmartButton *button);

private:
  int _pin;
  ClickAction _singleClickAction;
  ClickAction _longPressRepeatAction;
  ClickAction _longPressAction;
};

/**
* This is a SingleClickButton with no long press and long press repeat support.
*/
class SingleClickButtonConfiguration : public GenericButtonConfiguration {
public:
  SingleClickButtonConfiguration(int pin, ClickAction singleClickAction)
    : GenericButtonConfiguration(pin, singleClickAction, []() {}, []() {}) {}
};

/**
* This is a SingleClickButton which triggers the same action when long pressed.
*/
class SingleClickRepeatButtonConfiguration : public GenericButtonConfiguration {
public:
  SingleClickRepeatButtonConfiguration(int pin, ClickAction singleClickAction)
    : GenericButtonConfiguration(pin, singleClickAction, singleClickAction, []() {}) {}
};

void configureButtons();