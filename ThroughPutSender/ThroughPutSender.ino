#include <SPI.h>
#include <LoRa.h>

const int PACKET_SIZE = 32; // Size of the packet to be transmitted in bytes

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections!");
    while (true);
  }

}

void loop() {
  // Generate a packet with random data
  byte packet[PACKET_SIZE];
  for (int i = 0; i < PACKET_SIZE; i++) {
    packet[i] = random(256);
  }
  Serial.println(sizeof(packet));

  // Send the LoRa packet
  LoRa.beginPacket();
  LoRa.write(packet, PACKET_SIZE);
  Serial.println(PACKET_SIZE);
  LoRa.endPacket();

  delay(1000); // Wait for 1 second before sending the next packet
} 