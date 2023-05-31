#include <SPI.h>
#include <LoRa.h>

#define SENDER_NODE true
#define RECEIVER_NODE false

#define BAND 915E6  // Frequency band for LoRa communication

const int csPin = 10;     // LoRa chip select pin
const int resetPin = 9;   // LoRa reset pin
const int irqPin = 2;     // LoRa IRQ pin

const int packetSize = 32;  // Size of the LoRa packet
char receivedData[packetSize];  // Buffer to store received data

unsigned long sentTime;   // Time at which packet was sent

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (true);
  }

  LoRa.setPins(csPin, resetPin, irqPin);
  LoRa.onReceive(onReceive);

  if (SENDER_NODE) {
    Serial.println("Sender node");
    randomSeed(analogRead(0)); // Initialize random seed
  } else {
    Serial.println("Receiver node");
  }
}

void loop() {
  if (SENDER_NODE) {
    // Send a packet containing the current time
    sentTime = millis();
    Serial.print("Sending packet at time: ");
    Serial.println(sentTime);
    LoRa.beginPacket();
    LoRa.print(sentTime);
    LoRa.endPacket();
    delay(2000);  // Wait for 2 seconds before sending the next packet
  }
}

void onReceive(int packetSize) {
  if (!SENDER_NODE) {
    // Received a packet
    Serial.print("Received packet at time: ");
    unsigned long receivedTime = millis();
    Serial.println(receivedTime);
    Serial.print("Latency: ");
    Serial.println(receivedTime - atol(LoRa.readString().c_str()));
    Serial.println();
  }
}
