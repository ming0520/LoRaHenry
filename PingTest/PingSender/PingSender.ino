// LORA code for Transmitting Side
#include <SPI.h>
#include <LoRa.h>

unsigned long receiveTimestamp;
unsigned long sendTimestamp;
bool waitingMsg = false;
int counter = 0;
String roadType = "curve";
int distance = 100;

void setup() {

  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("Latency,unit,counter,road,distance");
}

void loop() {
  // String message = "";
  int packetSize;
  char receivedChar = '1';
  
  if(!waitingMsg){
    sendTimestamp = millis();
    LoRa.beginPacket();
    Serial.println("#");
    LoRa.print("#");
    LoRa.endPacket();
    waitingMsg = true;
    Serial.println("Waiting msg...");
  }

  while (waitingMsg){
    packetSize = LoRa.parsePacket();
    
    if (packetSize && waitingMsg) {
      
      
      while (LoRa.available()) {
        receivedChar = (char)LoRa.read();
      }
      Serial.print("Recieved: ");
      Serial.println(receivedChar);
      if(receivedChar == '*'){
        receiveTimestamp = millis();
        calculateLatency();
        waitingMsg = false;
      }else{
        Serial.println("Timeout");
        waitingMsg = false;
      }
    } 
}
delay(1000);
counter++;

}

void calculateLatency() {
  unsigned long latency = receiveTimestamp - sendTimestamp;
  // Serial.print("Latency: ");
  Serial.print(latency);
  Serial.print(",ms,");
  Serial.print(counter);
  Serial.println(","+roadType+","+distance);
}