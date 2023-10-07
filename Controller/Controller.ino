#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN

const byte address[6] = "00001";
const byte commandEnable = 0x00;
const byte commandDisable = 0x01;

void setup() {
 pinMode(LED_BUILTIN, OUTPUT);
   radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {
  const char text[] = "Hello World";
  radio.write(&commandEnable, sizeof(commandEnable));
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  radio.write(&commandDisable, sizeof(commandDisable));

  delay(1000);      

}
