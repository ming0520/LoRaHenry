#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 10
#define RST_PIN 9
#define DI0_PIN 2

unsigned long sendTimestamp;

void setup() {
  Serial.begin(9600);
  LoRa.setPins(SS_PIN, RST_PIN, DI0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections!");
    while (1);
  }
}

void loop() {
  sendPing();
  delay(2000); // Delay between pings
}

void sendPing() {
  sendTimestamp = millis();
  LoRa.beginPacket();
  LoRa.print("PING");
  LoRa.endPacket();
}
