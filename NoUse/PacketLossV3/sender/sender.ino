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
  memset(packet, 0, packetSize);
  sprintf(packet, "Hello world %d", millis());

  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();

  Serial.print("Packet sent: ");
  Serial.println(packet);

  delay(1000);
}
