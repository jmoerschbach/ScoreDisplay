#include "ButtonConfiguration.h"

GenericButtonConfiguration::GenericButtonConfiguration(
    int pin, ClickAction singleClickAction, ClickAction longPressRepeatAction = []() {}, ClickAction longPressAction = []() {}) {
    _pin = pin;
    _singleClickAction = singleClickAction;
    _longPressRepeatAction = longPressRepeatAction;
    _longPressAction = longPressAction;
  }
   void GenericButtonConfiguration::event(SmartButton *button, SmartButton::Event event, int clickCounter) {
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

   bool GenericButtonConfiguration::isPressed(SmartButton *button) {
    return (digitalRead(_pin) == LOW) ? true : false;
  }