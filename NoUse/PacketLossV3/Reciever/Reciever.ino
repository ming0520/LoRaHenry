#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 10
#define RST_PIN 9
#define DI0_PIN 2

const int packetSize = 20;
char packet[packetSize];

bool detectPacketLoss() {
  unsigned long startTime = millis();

  // wait for packet to be received or timeout
  while (LoRa.available() == 0 && millis() - startTime < 1000) {
    delay(10);
  }

  // check if packet was received
  if (LoRa.available()) {
    return false;
  } else {
    return true;
  }
}

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
  // send packet
  memset(packet, 0, packetSize);
  sprintf(packet, "Hello world %d", millis());
  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();

  // detect packet loss
  bool packetLost = detectPacketLoss();

  // handle packet loss
  if (packetLost) {
    Serial.println("Packet lost");
  }

  // wait before sending next packet
  delay(1000);
}
