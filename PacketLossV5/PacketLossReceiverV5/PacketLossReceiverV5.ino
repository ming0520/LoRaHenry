#include <SPI.h>
#include <LoRa.h>

const int csPin = 10;
const int resetPin = 9;
const int irqPin = 2;
const int packetCount = 10;  // Number of packets to receive
int receivedCount = 0;
int successCount = 0;

String receivedData[packetCount];

void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (true);
  }
  Serial.println("LoRa Receiver Start");
}

void loop() {
  if (receivedCount < packetCount) {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      String received;

      while (LoRa.available()) {
        received += (char)LoRa.read();
      }

      receivedCount++;
      successCount++;
      Serial.println("Packet received: " + received);
    }
  } else {
    Serial.println("Packet receiving complete.");
    Serial.println("Success rate: " + String(successCount) + " out of " + String(packetCount));
    while (true);
  }

  // delay(1000);
}
