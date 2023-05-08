#include <SPI.h>
#include <LoRa.h>

#define PACKET_COUNT 10

int seq_no = 0;
int expected_seq_no = 0;
int missing_packets[PACKET_COUNT] = {0};
int missing_packet_count = 0;



void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");
  // LoRa.enableCrc();
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}


void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    // Serial.print("Received packet '");
    // char received_seq_no = (char)LoRa.read();
    // Serial.println("Received Seq:"+(char)LoRa.read());
 
    // read packet
    while (LoRa.available()) {
      byte packetBuffer[packetSize];
      int bytesRead = LoRa.readBytes(packetBuffer, packetSize);

// Convert the buffer to an integer
    int packetInt;
    memcpy(&packetInt, packetBuffer, sizeof(packetInt));
    packetInt = reinterpret_cast<int>(packetInt);
      Serial.print(packetInt);
    }

    // print RSSI of packet
    Serial.print(" RSSI: ");
    Serial.print(LoRa.packetRssi());
    Serial.print("' SNR: ");
    Serial.print(LoRa.packetSnr());
    Serial.println("");
  }
}
