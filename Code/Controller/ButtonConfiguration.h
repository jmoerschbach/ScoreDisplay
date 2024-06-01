#include <SmartButton.h>

using namespace smartbutton;

/**
* This is a small wrapper class to ease the usage of the SmartButton-Api.
* It offers the possibility to define a button's function via lambdas for single click, long press and long press repeat events.
*/
class GenericButtonConfiguration : public SmartButtonInterface {
  using ClickAction = void (*)(void);
public:
  GenericButtonConfiguration(
    int pin, ClickAction singleClickAction, ClickAction longPressRepeatAction = []() {}, ClickAction longPressAction = []() {}) {
    _pin = pin;
    _singleClickAction = singleClickAction;
    _longPressRepeatAction = longPressRepeatAction;
    _longPressAction = longPressAction;
  }
  virtual void event(SmartButton *button, SmartButton::Event event, int clickCounter) {
    if (event == SmartButton::Event::CLICK) {
      if (clickCounter == 1) {
        _singleClickAction();
      }
    } else if (event == SmartButton::Event::HOLD) {
      _longPressAction();
    } else if (event == SmartButton::Event::HOLD_REPEAT || event == SmartButton::Event::LONG_HOLD_REPEAT) {
      _longPressRepeatAction();
    }
  }

  virtual bool isPressed(SmartButton *button) {
    return (digitalRead(_pin) == LOW) ? true : false;
  }

private:
  int _pin;
  ClickAction _singleClickAction;
  ClickAction _longPressRepeatAction;
  ClickAction _longPressAction;
};