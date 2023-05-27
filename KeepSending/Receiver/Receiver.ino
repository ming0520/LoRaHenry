// LORA code for Receiver Side


#include <SPI.h>

#include <LoRa.h>


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

  // try to parse packet

  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    // received a packet

    // Serial.print("Received packet '");


    // read packet

    while (LoRa.available()) {

      Serial.print((char)LoRa.read());

    }


    // print RSSI of packet

    Serial.print(",");
    Serial.print(LoRa.packetRssi());
    Serial.print(",");
    Serial.print(LoRa.packetFrequencyError()); 
    Serial.print(",");
    Serial.println(LoRa.packetSnr());
  }

}