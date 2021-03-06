#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    float text[32];
    radio.read(&text, sizeof(text));
    Serial.print("LDR Value");Serial.print(",");Serial.print("  Humidity");Serial.print(",");Serial.println("  Temperature");
    Serial.print(text[0]);Serial.print("     \t");Serial.print(text[1]);Serial.print("\t");Serial.println(text[2]);
  }
  delay(1000);
}
