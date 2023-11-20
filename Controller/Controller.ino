#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Commands.h"

RF24 radio(10, 9);  // CE, CSN

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
  if (Serial.available()) {
    byte command = Serial.parseInt();
    Serial.write(command);

    radio.write(&command, 1);
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  }
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
}
