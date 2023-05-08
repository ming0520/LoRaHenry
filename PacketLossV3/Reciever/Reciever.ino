#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 10
#define RST_PIN 9
#define DI0_PIN 2

const int packetSize = 20;
char packet[packetSize];

void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(SS_PIN, RST_PIN, DI0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      String received = LoRa.readString();
      Serial.print("Packet received: ");
      Serial.println(received);
    }
  }
}
