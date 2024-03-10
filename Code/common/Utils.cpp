#include "Utils.h"

TwoDigit convert2DecimalDigit(uint8_t value) {
  TwoDigit result;
  if (value > 99) {
    result.firstDigit = 10;   //everything greater 9 is considered as invalid
    result.secondDigit = 10;  //everything greater 9 is considered as invalid
    return result;
  }
  
  uint8_t firstDigit = value / 10;
  uint8_t secondDigit = value - (firstDigit * 10);

  result.firstDigit = firstDigit;
  result.secondDigit = secondDigit;
  return result;
}