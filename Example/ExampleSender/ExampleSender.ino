// LORA code for Transmitting Side
#include <SPI.h>
#include <LoRa.h>

const int packetCount = 20;  // Number of packets to send
int sentCount = 0;

void setup() {

  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setTxPower(20);

  LoRa.beginPacket();
  Serial.println("#");
  LoRa.print("#");
  LoRa.endPacket();
  delay(1000);
}

void loop() {

  if(sentCount < packetCount+1){
    Serial.print("Sending packet: ");
    Serial.println(sentCount);

    // send packet
    LoRa.beginPacket();
    LoRa.print(sentCount);
    LoRa.endPacket();

    sentCount++;
  }else {
    Serial.println("Packet sending complete.");
    while (true){
      // LoRa.beginPacket();
      // Serial.println("*");
      // LoRa.print("*");
      // LoRa.endPacket();
      // delay(1000);
    }
  }
  
  delay(1000);

}