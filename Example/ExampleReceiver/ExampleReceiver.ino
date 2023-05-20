// LORA code for Receiver Side
#include <SPI.h>
#include <LoRa.h>

const int packetCount = 5;  // Number of packets to receive
int receivedCount = 0;
int successCount = 0;
bool stopFlag = true;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  int packetSize;
  while(stopFlag){
    packetSize = LoRa.parsePacket();
    if (packetSize) {
      while (LoRa.available()) {
        char receivedChar = (char)LoRa.read();
        Serial.println(receivedChar);
        if(receivedChar == '#'){
          Serial.println("Break");
          stopFlag = false;
        }
      }
    }
  // delay(1000);
  }

  // try to parse packet
    packetSize = LoRa.parsePacket();

    if (packetSize) {
      // received a packet
      Serial.print("Received packet '");
      // read packet
      while (LoRa.available()) {
        receivedCount = (int)LoRa.read()-(int)'0';
        if (receivedCount < packetCount && receivedCount >= 0){
          Serial.print(receivedCount);
          successCount++;
        }         
      }

      if(receivedCount == -6){
        Serial.println("Packet receiving complete.");
        Serial.println(receivedCount);
        Serial.println("Success rate: " + String(successCount) + " out of " + String(packetCount));
        while (true);       
      }

     // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());         
  }

}

