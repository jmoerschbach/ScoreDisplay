#include <FastLED.h>
#include <RF24.h>

struct BatteryPacket {
  int rawValue = 0;
  float voltage = 0;
  int soc = 0;
  int lbo = 0;
  int counter = 0;
};

constexpr uint8_t ADDRESS_MAIN_DISPLAY[6] = "MAIN0";
constexpr float factor = 0.004882813;

#define LEDS_PER_SEGMENT 11
#define NUM_LEDS (2 * 7 * LEDS_PER_SEGMENT)

CRGB _leds[NUM_LEDS];

constexpr int DATA_PIN_LEDS = A0;
constexpr int BATTERY_PIN = A6;
constexpr int LBO_PIN = 2;
constexpr int HORN_PIN = 0;
int counter = 0;
RF24 radio(9, 10);  // CE, CSN

BatteryPacket data;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN_LEDS>(_leds, NUM_LEDS);
  FastLED.setBrightness(128);
  // Serial.begin(9600);

  fill_solid(_leds, NUM_LEDS, CRGB::Red);


  radio.begin();
  radio.setChannel(110);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  FastLED.show();
  pinMode(LBO_PIN, INPUT);
  pinMode(HORN_PIN, OUTPUT);
  pinMode(BATTERY_PIN, INPUT);
}
void loop() {

  //turn leds off and wait
  // FastLED.clear();
  // FastLED.show();
  // delay(100);
  // measureAndSend();
  // radio.openWritingPipe(ADDRESS_MAIN_DISPLAY);
  // radio.write(&data, sizeof(data));

  // // turn leds on and wait
  // fill_solid(_leds, NUM_LEDS, CRGB::Red);
  // FastLED.show();
  // delay(100);
  measureAndSend();
  radio.openWritingPipe(ADDRESS_MAIN_DISPLAY);
  radio.write(&data, sizeof(data));

  counter++;
  // Serial.println(data.rawValue);
  for (uint8_t i = 0; i < 6; i++) {
    delay(10 * 1000);
  }
}

void measureAndSend() {
  int rawInput = measure(10);
  int lbo = digitalRead(LBO_PIN);
  int soc = map(rawInput, 710, 817, 0, 100);


  data.rawValue = rawInput;
  data.voltage = rawInput * factor;
  data.lbo = lbo;
  data.soc = soc;
  data.counter = counter;
}

int measure(uint8_t numberOfMeausers) {

  int rawValue = 0;
  for (uint8_t i = 0; i < numberOfMeausers; i++) {
    rawValue += analogRead(BATTERY_PIN);
  }

  return rawValue / numberOfMeausers;
}
