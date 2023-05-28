// LORA code for Receiver Side
#include <SPI.h>
#include <LoRa.h>

const int packetCount = 9999;  // Number of packets to receive
int receivedCount = 0;
int successCount = 0;
bool stopFlag = false;
bool waitingMsg = true;

void setup() {
  // LoRa.setTxPower(20);
  successCount = 0;
  receivedCount = 0;
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("packet id,success count,RSSI,frequency error,SNR");
}

void loop() {
  int packetSize;
  packetSize = LoRa.parsePacket();
  char receivedChar = '1';
  if (packetSize) {
    while (LoRa.available()) {
      receivedChar = (char)LoRa.read();
    }

    Serial.println(receivedChar);
    if(receivedChar == '#'){
    LoRa.beginPacket();
    Serial.println("*");
    LoRa.print("*");
    LoRa.endPacket();      
    }

  }


}

