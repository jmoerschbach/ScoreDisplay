#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Commands.h"

RF24 radio(9,10);  // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // digitalWrite(LED_BUILTIN, LOW);
  radio.write(0x09, 1);
  delay(500);
  radio.write(0x0A, 1);
  //  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);

  // if (Serial.available()) {
  //   byte command = Serial.parseInt();
  //   Serial.write(command);

  //   radio.write(&command, 1);
  //   digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // }
  // digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
}
