#include <SPI.h>
#include <LoRa.h>

#define PACKET_SIZE 20
#define NUM_PACKETS 100

byte packet[PACKET_SIZE];
unsigned int num_tx_packets = 0;
unsigned int num_rx_packets = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (1);
  }

  LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(7);
}

void loop() {
  // if (num_tx_packets < NUM_PACKETS) {
  //   // generate a random packet
  //   for (int i = 0; i < PACKET_SIZE; i++) {
  //     packet[i] = random(256);
  //   }

  //   // transmit the packet
  //   LoRa.beginPacket();
  //   LoRa.write(packet, PACKET_SIZE);
  //   Serial.println("PACKET_SIZE: " + String(PACKET_SIZE));
  //   LoRa.endPacket();
  //   num_tx_packets++;
  // }

  // check for received packets
  if (LoRa.parsePacket()) {
    while (LoRa.available()) {
      LoRa.read();
    }
    num_rx_packets++;
  }

  // calculate packet loss
  float packet_loss = ((float)(num_tx_packets - num_rx_packets) / (float)num_tx_packets) * 100.0;
  Serial.print("Packet loss: ");
  Serial.print(packet_loss);
  Serial.println("%");

  delay(1000);
}