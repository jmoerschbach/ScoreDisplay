#include <RF24.h>
struct BatteryPacket {
  int rawValue = 0;
  float voltage = 0;
  int soc = 0;
  int lbo = 0;
  int counter = 0;
};

RF24 radio(10, 9);  // CE, CSN
constexpr uint8_t ADDRESS_MAIN_DISPLAY[6] = "MAIN0";
constexpr float factor = 0.004783354;

BatteryPacket data;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(110);
  radio.openReadingPipe(0, ADDRESS_MAIN_DISPLAY);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

  Serial.println("Ready to receive");

}


void loop() {

  if (radio.available()) {
    radio.read(&data, sizeof(data));

    float voltage = data.rawValue * factor;
    Serial.print(data.counter);
    Serial.print(": raw: ");
    Serial.print(data.rawValue);
    Serial.print(", voltage: ");
    Serial.print(voltage,3);
    Serial.print(", soc: ");
    Serial.print(data.soc);
    Serial.print(", lbo: ");
    Serial.println(data.lbo);
    
  }
}



