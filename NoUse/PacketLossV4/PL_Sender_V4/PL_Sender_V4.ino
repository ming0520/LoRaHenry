#include <SPI.h>
#include <LoRa.h>

const int csPin = 10;
const int resetPin = 9;
const int irqPin = 2;
const int packetCount = 100;  // Number of packets to send
int sentCount = 0;
int successCount = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (true);
  }
}

void loop() {
  if (sentCount < packetCount) {
    String packet = "Hello, packet number " + String(sentCount);

    LoRa.beginPacket();
    LoRa.print(packet);
    LoRa.endPacket();

    sentCount++;
    Serial.println("Packet sent: " + packet);
  } else {
    Serial.println("Packet sending complete.");
    while (true);
  }

  delay(1000);
}
