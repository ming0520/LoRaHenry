#include <SPI.h>
#include <LoRa.h>

unsigned long startTime;
unsigned long endTime;
unsigned long totalBytesReceived = 0;

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
  // Check if a LoRa packet is available
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    startTime = millis();

    // Read the received packet
    while (LoRa.available()) {
      LoRa.read();
    }

    endTime = millis();

      
    // Calculate the received bytes and download speed
    int receivedBytes = packetSize;
    float downloadTime = (endTime - startTime); // Time in seconds
    float downloadSpeed = receivedBytes / (downloadTime/1000); // Speed in bytes per second

    totalBytesReceived += receivedBytes;
    Serial.print("Packet: ");
    Serial.print(packetSize);
    Serial.print(" Received ");
    Serial.print(receivedBytes);
    Serial.print(" bytes in ");
    Serial.print(downloadTime);
    Serial.print(" ms. Download speed: ");
    Serial.print(downloadSpeed);
    Serial.println(" Bps");

    Serial.print("Total bytes received: ");
    Serial.println(totalBytesReceived);
  }

}