// LORA code for Receiver Side
#include <SPI.h>
#include <LoRa.h>

const int packetCount = 20;  // Number of packets to receive
int receivedCount = 0;
int successCount = 0;
bool stopFlag = true;

void setup() {
  LoRa.setTxPower(txPower);
  successCount = 0;
  receivedCount = 0;
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
      
      // read packet
      String message = "";
      while (LoRa.available()) {
        // receivedCount =  String((char)LoRa.read()).toInt();
        
        // receivedCount = (int)LoRa.read()-(int)'0'; 
        message += (char)LoRa.read();   
      }
      receivedCount = message.toInt();
      if (receivedCount < packetCount && receivedCount >= 0){
        Serial.print("Received packet ");
        Serial.print(receivedCount);
        successCount = successCount + 1;
        Serial.print(" Success Count:" + String(successCount));
      }else{
        Serial.println("Packet receiving complete.");
        Serial.println(receivedCount);
        Serial.println("Success rate: " + String(successCount) + " out of " + String(packetCount));
        while (true);       
      }          

      // if(receivedCount == -6){
      //   Serial.println("Packet receiving complete.");
      //   Serial.println(receivedCount);
      //   Serial.println("Success rate: " + String(successCount) + " out of " + String(packetCount));
      //   while (true);       
      // }



     // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    Serial.print("' Packet Frequency Error: ");
    Serial.println(LoRa.packetFrequencyError()); 
    Serial.print("' packetSnr ");
    Serial.println(LoRa.packetSnr());             
  }

}

